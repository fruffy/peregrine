# eBPF questions
In this experiment, I tested GPT 3 & 4 with BPF programs for both code generation and understanding. I asked them to generate the BPF assembly code for given tcpdump command for code generation, and give them BPF assembly code and ask them to give inline comments then construct the equivalent tcpdump command for the given BPF program.

## Models for comparision

-   GPT3 (chatgpt)
-   GPT4 (new bing chat)

## Prompt
Could you show me what {command} possibly compile to?

## Code Generation
1. `sudo tcpdump -i en0 -d icmp`\
Local Result (MacOS, M1 chip):
```
(000) ldh      [12]
(001) jeq      #0x800           jt 2	jf 5
(002) ldb      [23]
(003) jeq      #0x1             jt 4	jf 5
(004) ret      #524288
(005) ret      #0
```
GPT3:
```
(000) ldh      [12]
(001) jeq      #0x800           jt 2    jf 5             # <---- ethertype for IP
(002) ldb      [23]
(003) jeq      #0x1             jt 4    jf 5             # <---- IP protocol number for ICMP
(004) ret      #262144
(005) ret      #
```

2. `sudo tcpdump -y RAW -d tcp dst port 8080`\
Local Result (MacOS, M1 chip):
```
tcpdump: data link type RAW
(000) ldb      [0]
(001) and      #0xf0
(002) jeq      #0x60            jt 3	jf 7
(003) ldb      [6]
(004) jeq      #0x6             jt 5	jf 18
(005) ldh      [42]
(006) jeq      #0x1f90          jt 17	jf 18
(007) ldb      [0]
(008) and      #0xf0
(009) jeq      #0x40            jt 10	jf 18
(010) ldb      [9]
(011) jeq      #0x6             jt 12	jf 18
(012) ldh      [6]
(013) jset     #0x1fff          jt 18	jf 14
(014) ldxb     4*([0]&0xf)
(015) ldh      [x + 2]
(016) jeq      #0x1f90          jt 17	jf 18
(017) ret      #524288
(018) ret      #0
```
GPT3:
```
(000) ldb      [0]
(001) jeq      #0x0             jt 2    jf 4             # <---- link-layer type RAW
(002) ldb      [14]
(003) jeq      #0x6             jt 5    jf 13            # <---- ethertype for TCP
(004) ret      #
(005) ldh      [2]
(006) jeq      #0x1f90          jt 7    jf 13            # <---- TCP destination port 8080
(007) ret      #262144
(008) ldh      [2]
(009) jeq      #0x1f90          jt 13   jf 10            # <---- TCP source port 8080
(010) ret      #262144
(011) ret      #
```
GPT 4:
```
(000) ldh      [12]
(001) jeq      #0x800           jt 2    jf 6
(002) ldb      [23]
(003) jeq      #0x6             jt 4    jf 6
(004) ldh      [20]
(005) jeq      #0x1f90          jt 7    jf 6
(006) ret      #0
(007) ret      #65535
```


3. `sudo tcpdump -i en0 "dst host 192.168.1.0" -d`\
Local Result (MacOS, M1 chip):
```
(000) ldh      [12]
(001) jeq      #0x800           jt 2	jf 4
(002) ld       [30]
(003) jeq      #0xc0a80100      jt 8	jf 9
(004) jeq      #0x806           jt 6	jf 5
(005) jeq      #0x8035          jt 6	jf 9
(006) ld       [38]
(007) jeq      #0xc0a80100      jt 8	jf 9
(008) ret      #524288
(009) ret      #0
```
GPT3:
```
(000) ldh      [12]
(001) jeq      #0x800           jt 2    jf 9             # <---- ethertype for IP
(002) ldh      [16]
(003) jeq      #0xc0a8          jt 10   jf 9             # <---- IP destination address first octet 192
(004) ldh      [18]
(005) jeq      #0x0100          jt 6    jf 9             # <---- IP destination address second octet 168
(006) ldh      [20]
(007) jeq      #0x0100          jt 8    jf 9             # <---- IP destination address third octet 1
(008) jeq      #0x0000          jt 11   jf 9             # <---- IP destination address fourth octet 0
(009) ret      #
(010) ret      #
(011) ret      #
```
GPT4:
```
(000) ldh      [12]
(001) jeq      #0x800           jt 2    jf 6
(002) ld       [26]
(003) jeq      #0xc0a80100      jt 5    jf 6
(004) ret      #65535
(005) ret      #0
```
## Prompt
Given this BPF program, could you give inline comment and construct the possible equivalent tcpdump command?

## Code Understanding
1. 
tcpdump command:
`sudo tcpdump -y RAW -d tcp dst port 8080`\

BPF program:
```
(000) ldb      [0]
(001) and      #0xf0
(002) jeq      #0x60            jt 3    jf 7
(003) ldb      [6]
(004) jeq      #0x6             jt 5    jf 18
(005) ldh      [42]
(006) jeq      #0x1f90          jt 17   jf 18
(007) ldb      [0]
(008) and      #0xf0
(009) jeq      #0x40            jt 10   jf 18
(010) ldb      [9]
(011) jeq      #0x6             jt 12   jf 18
(012) ldh      [6]
(013) jset     #0x1fff          jt 18   jf 14
(014) ldxb     4*([0]&0xf)
(015) ldh      [x + 2]
(016) jeq      #0x1f90          jt 17   jf 18
(017) ret      #262144
(018) ret      #0
```

GPT3:
```
(000) ldb      [0]          ; Load byte at offset 0 into register
(001) and      #0xf0        ; Perform bitwise AND operation with 0xf0
(002) jeq      #0x60        ; If the result is equal to 0x60, jump to line 3, else jump to line 7
(003) ldb      [6]          ; Load byte at offset 6 into register
(004) jeq      #0x6         ; If the result is equal to 0x6, jump to line 5, else jump to line 18
(005) ldh      [42]         ; Load half-word (2 bytes) at offset 42 into register
(006) jeq      #0x1f90      ; If the result is equal to 0x1f90, jump to line 17, else jump to line 18
(007) ldb      [0]          ; Load byte at offset 0 into register
(008) and      #0xf0        ; Perform bitwise AND operation with 0xf0
(009) jeq      #0x40        ; If the result is equal to 0x40, jump to line 10, else jump to line 18
(010) ldb      [9]          ; Load byte at offset 9 into register
(011) jeq      #0x6         ; If the result is equal to 0x6, jump to line 12, else jump to line 18
(012) ldh      [6]          ; Load half-word (2 bytes) at offset 6 into register
(013) jset     #0x1fff      ; If any of the 13 least significant bits are set, jump to line 18, else jump to line 14
(014) ldxb     4*([0]&0xf)  ; Load the address offset by 4 times the lower 4 bits of the value at offset 0 into register
(015) ldh      [x + 2]      ; Load half-word (2 bytes) from the calculated address into register
(016) jeq      #0x1f90      ; If the result is equal to 0x1f90, jump to line 17, else jump to line 18
(017) ret      #262144      ; Return with a value of 262144
(018) ret      #0           ; Return with a value of 0
```
`tcpdump '((ether[0] & 0xf0) == 0x60) and (ip[6] == 0x6) and (tcp[2:2] == 0x1f90) or ((ether[0] & 0xf0) == 0x40) and (ip[9] == 0x6) and (tcp[6:2] == 0x1f90)'`


GPT4:
```
(000) ldb      [0]              // Load the first byte of the packet into the accumulator
(001) and      #0xf0            // Perform a bitwise AND operation on the accumulator with 0xf0
(002) jeq      #0x60            jt 3    jf 7 // If the result is equal to 0x60 (IPv6), jump to instruction 3, else jump to instruction 7
(003) ldb      [6]              // Load the byte at offset 6 into the accumulator
(004) jeq      #0x6             jt 5    jf 18 // If the result is equal to 6 (TCP), jump to instruction 5, else jump to instruction 18
(005) ldh      [42]             // Load the half-word at offset 42 into the accumulator
(006) jeq      #0x1f90          jt 17   jf 18 // If the result is equal to 8080, jump to instruction 17, else jump to instruction 18
(007) ldb      [0]              // Load the first byte of the packet into the accumulator
(008) and      #0xf0            // Perform a bitwise AND operation on the accumulator with 0xf0
(009) jeq      #0x40            jt 10   jf 18 // If the result is equal to 0x40 (IPv4), jump to instruction 10, else jump to instruction 18
(010) ldb      [9]              // Load the byte at offset 9 into the accumulator
(011) jeq      #0x6             jt 12   jf 18 // If the result is equal to 17 (UDP), jump to instruction 12, else jump to instruction 18
(012) ldh      [6]              // Load the half-word at offset 6 into the accumulator
(013) jset     #0x1fff          jt 18   jf 14 // If any of the bits in positions specified by mask (8191 or lower) are set, jump to instruction 18, else jump to instruction 14
(014) ldxb     4*([0]&0xf)      // Load into index register: length of IP header *4 (since it's in words)
(015) ldh      [x + 2]          // Load half-word at offset x+2 into accumulator
(016) jeq      #0x1f90          jt 17   jf 18 // If result is equal to port number (8080), jump to instruction 17, else jump to instruction 18
(017) ret      #262144          // Return a verdict of "pass" with a value of maximum packet length (262144)
(018) ret      #0               // Return a verdict of "drop" with a value of zero.
```
`tcpdump 'tcp port 8080 and ip6 or udp src port 8080 and ip'`

2. 
tcpdump command:
`sudo tcpdump -i en0 "dst host 192.168.1.0" -d`\
BPF Program:
```
(000) ldh      [12]
(001) jeq      #0x800           jt 2	jf 4
(002) ld       [30]
(003) jeq      #0xc0a80100      jt 8	jf 9
(004) jeq      #0x806           jt 6	jf 5
(005) jeq      #0x8035          jt 6	jf 9
(006) ld       [38]
(007) jeq      #0xc0a80100      jt 8	jf 9
(008) ret      #524288
(009) ret      #0
```

GPT3:
```
(000) ldh      [12]              ; Load half-word (2 bytes) from offset 12 (Ethernet header type) into register
(001) jeq      #0x800           ; If the loaded value is equal to 0x800 (IPv4), jump to line 2, else jump to line 4
(002) ld       [30]              ; Load word (4 bytes) from offset 30 (IP source address) into register
(003) jeq      #0xc0a80100      ; If the loaded value is equal to 192.168.1.0, jump to line 8, else jump to line 9
(004) jeq      #0x806           ; If the loaded value is equal to 0x806 (ARP), jump to line 6, else jump to line 5
(005) jeq      #0x8035          ; If the loaded value is equal to 0x8035, jump to line 6, else jump to line 9
(006) ld       [38]              ; Load word (4 bytes) from offset 38 (ARP target IP address) into register
(007) jeq      #0xc0a80100      ; If the loaded value is equal to 192.168.1.0, jump to line 8, else jump to line 9
(008) ret      #524288           ; Return with a value of 524288 (indicating a match)
(009) ret      #0                ; Return with a value of 0 (indicating no match)
```
`tcpdump 'ether[12:2] = 0x800 and (ip[30:4] = 192.168.1.0 or arp)'`

GPT4:
```
(000) ldh      [12]             // Load the half-word at offset 12 into the accumulator
(001) jeq      #0x800           jt 2    jf 4 // If the result is equal to 0x800 (IPv4), jump to instruction 2, else jump to instruction 4
(002) ld       [30]             // Load the word at offset 30 into the accumulator
(003) jeq      #0xc0a80100      jt 8    jf 9 // If the result is equal to 192.168.1.0, jump to instruction 8, else jump to instruction 9
(004) jeq      #0x806           jt 6    jf 5 // If the result is equal to 0x806 (ARP), jump to instruction 6, else jump to instruction 5
(005) jeq      #0x8035          jt 6    jf 9 // If the result is equal to 0x8035 (RARP), jump to instruction 6, else jump to instruction 9
(006) ld       [38]             // Load the word at offset 38 into the accumulator
(007) jeq      #0xc0a80100      jt 8    jf 9 // If the result is equal to 192.168.1.0, jump to instruction 8, else jump to instruction 9
(008) ret      #524288          // Return a verdict of "pass" with a value of maximum packet length (524288)
(009) ret      #0               // Return a verdict of "drop" with a value of zero.
```
`tcpdump 'ip dst host 192.168.1.0 or arp or rarp'`

3. tcpdump command: `sudo tcpdump -i en0 -nn -s0 -v port 80 -d`\
BPF code:
```
(000) ldh      [12]
(001) jeq      #0x86dd          jt 2	jf 10
(002) ldb      [20]
(003) jeq      #0x84            jt 6	jf 4
(004) jeq      #0x6             jt 6	jf 5
(005) jeq      #0x11            jt 6	jf 23
(006) ldh      [54]
(007) jeq      #0x50            jt 22	jf 8
(008) ldh      [56]
(009) jeq      #0x50            jt 22	jf 23
(010) jeq      #0x800           jt 11	jf 23
(011) ldb      [23]
(012) jeq      #0x84            jt 15	jf 13
(013) jeq      #0x6             jt 15	jf 14
(014) jeq      #0x11            jt 15	jf 23
(015) ldh      [20]
(016) jset     #0x1fff          jt 23	jf 17
(017) ldxb     4*([14]&0xf)
(018) ldh      [x + 14]
(019) jeq      #0x50            jt 22	jf 20
(020) ldh      [x + 16]
(021) jeq      #0x50            jt 22	jf 23
(022) ret      #524288
(023) ret      #0
```

GPT3:
```
(000) ldh      [12]              ; Load half-word (2 bytes) from offset 12 (Ethernet header type) into register
(001) jeq      #0x86dd          ; If the loaded value is equal to 0x86dd (IPv6), jump to line 2, else jump to line 10
(002) ldb      [20]              ; Load byte from offset 20 (IPv4 header protocol) into register
(003) jeq      #0x84            ; If the loaded value is equal to 0x84 (ARP), jump to line 6, else jump to line 4
(004) jeq      #0x6             ; If the loaded value is equal to 0x6 (TCP), jump to line 6, else jump to line 5
(005) jeq      #0x11            ; If the loaded value is equal to 0x11 (UDP), jump to line 6, else jump to line 23
(006) ldh      [54]              ; Load half-word (2 bytes) from offset 54 (IPv6 next header) into register
(007) jeq      #0x50            ; If the loaded value is equal to 0x50 (ESP), jump to line 22, else jump to line 8
(008) ldh      [56]              ; Load half-word (2 bytes) from offset 56 (IPv6 next header) into register
(009) jeq      #0x50            ; If the loaded value is equal to 0x50 (AH), jump to line 22, else jump to line 23
(010) jeq      #0x800           ; If the loaded value is equal to 0x800 (IPv4), jump to line 11, else jump to line 23
(011) ldb      [23]              ; Load byte from offset 23 (IPv4 header protocol) into register
(012) jeq      #0x84            ; If the loaded value is equal to 0x84 (ARP), jump to line 15, else jump to line 13
(013) jeq      #0x6             ; If the loaded value is equal to 0x6 (TCP), jump to line 15, else jump to line 14
(014) jeq      #0x11            ; If the loaded value is equal to 0x11 (UDP), jump to line 15, else jump to line 23
(015) ldh      [20]              ; Load half-word (2 bytes) from offset 20 (IPv4 header destination port) into register
(016) jset     #0x1fff          ; If any of the 13 least significant bits are set, jump to line 23, else jump to line 17
(017) ldxb     4*([14]&0xf)     ; Load address offset by 4 times the lower 4 bits of the value at offset 14 into register
(018) ldh      [x + 14]          ; Load half-word (2 bytes) from the calculated address into register
(019) jeq      #0x50            ; If the loaded value is equal to 0x50 (ESP), jump to line 22, else jump to line 20
(020) ldh      [x + 16]          ; Load half-word (2 bytes) from the calculated address into register
(021) jeq      #0x50            ; If the loaded value is equal to 0x50 (AH), jump to line 22, else jump to line 23
(022) ret      #524288           ; Return with a value of 524288 (indicating a match)
(023) ret      #0                ; Return with a value of 0 (indicating no match)
```
`tcpdump 'ether proto 0x86dd or (ether proto 0x800 and (ip proto 0x84 or ip proto 0x6 or ip proto 0x11) or (ip6 proto 0x50 or ip6 proto 0x51) or (ip proto 0x800 and (ip proto 0x84 or ip proto 0x6 or ip proto 0x11) and (tcp port 80 or udp port 80)))'`

GPT4:
```
(000) ldh      [12]             // Load the half-word at offset 12 into the accumulator
(001) jeq      #0x86dd          jt 2    jf 10 // If the result is equal to 0x86dd (IPv6), jump to instruction 2, else jump to instruction 10
(002) ldb      [20]             // Load the byte at offset 20 into the accumulator
(003) jeq      #0x84            jt 6    jf 4 // If the result is equal to 132 (SCTP), jump to instruction 6, else jump to instruction 4
(004) jeq      #0x6             jt 6    jf 5 // If the result is equal to 6 (TCP), jump to instruction 6, else jump to instruction 5
(005) jeq      #0x11            jt 6    jf 23 // If the result is equal to 17 (UDP), jump to instruction 6, else jump to instruction 23
(006) ldh      [54]             // Load the half-word at offset 54 into the accumulator
(007) jeq      #0x50            jt 22   jf 8 // If the result is equal to port number (80), jump to instruction 22, else jump to instruction 8
(008) ldh      [56]             // Load the half-word at offset 56 into the accumulator
(009) jeq      #0x50            jt 22   jf 23 // If the result is equal to port number (80), jump to instruction 22, else jump to instruction 23
(010) jeq      #0x800           jt 11   jf 23 // If the result is equal to 0x800 (IPv4), jump to instruction 11, else jump to instruction 23
(011) ldb      [23]             // Load the byte at offset 23 into the accumulator
(012) jeq      #0x84            jt 15   jf 13 // If the result is equal to port number (132), jump to instruction 15, else jump to instruction 13
(013) jeq      #0x6             jt 15   jf 14 // If the result is equal to port number (6), jump to instruction 15, else jump to instruction 14
(014) jeq      #0x11            jt 15   jf 23 // If the result is equal to port number (17), jump to instruction 15, else jump to instruction 23
(015) ldh      [20]             // Load half-word at offset of IP header length into accumulator
(016) jset     #0x1fff          jt 23   jf 17 // If any of the bits in positions specified by mask (8191 or lower) are set, jump to instruction 23, else jump to instruction17
(017) ldxb     4*([14]&0xf)     // Load into index register: length of IP header *4 (since it's in words)
(018) ldh      [x +14]          // Load half-word at offset x+14 into accumulator
(019) jeq      #0x50            jt22    jf20 // If result is equal to port number (80), jump to instruction22, else jump to instruction20
(020) ldh      [x +16]          // Load half-word at offset x+16 into accumulator
(021) jeq      #0x50            jt22    jf23 // If result is equal to port number (80), jump to instruction22, else jump to instruction23
(022) ret      #524288          // Return a verdict of "pass" with a value of maximum packet length (524288)
(023) ret      #0               // Return a verdict of "drop" with a value of zero.
```
`tcpdump 'port http'`