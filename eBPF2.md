# eBPF questions
In this experiment, I tested GPT 3 & 4 with BPF programs for both code generation and understanding. I asked them to generate the BPF assembly code for given tcpdump command for code generation, and give them BPF assembly code and ask them to give inline comments then construct the equivalent tcpdump command for the given BPF program.

## Models for comparision

-   GPT3 (chatgpt)
-   GPT4 (new bing chat)

## Local Machine Set Up
I set up the docker with [Dockerfile](https://github.com/singe/ebpf-docker-for-mac/blob/main/Dockerfile) on a MacOS with M1 chip (ARM64). The docker image is Ubuntu 22.04.2, kernel release version is 5.15.49-linuxkit.

## Prompt
For example, the bytecode for program
```
int hello(void *ctx) {
    bpf_trace_printk("Hello world\\n");
    return 0;
}
``` 
is
```
0000000000000000 <hello>:
       0:	18 01 00 00 00 00 00 00 00 00 00 00 00 00 00 00	r1 = 0 ll
       2:	85 10 00 00 ff ff ff ff	call -1
       3:	b7 00 00 00 00 00 00 00	r0 = 0
       4:	95 00 00 00 00 00 00 00	exit
``` 
Suppose the toolchain is eBPF, the architecture is ARM64, could you give me the bytecode similar to above for the following program:

## 1.
program: 
```
__attribute__((section("raw_tracepoint/sys_enter"), used))
void bpf_openat_parser()
{
}
```
Local Machine:
```
0000000000000000 <bpf_openat_parser>:
       0:	95 00 00 00 00 00 00 00	exit
```

GPT3:
```
0000000000000000 <bpf_openat_parser>:
       0:	b7 00 00 00 00 00 00 00	r0 = 0
       1:	95 00 00 00 00 00 00 00	exit
```

## 2.
program:
```
__attribute__((section("raw_tracepoint/sys_enter"), used))
int bpf_openat_parser(struct bpf_raw_tracepoint_args *ctx)
{
    unsigned long syscall_id = ctx->args[1];
    volatile struct pt_regs *regs;
    volatile const char *pathname;

    if (syscall_id != __NR_openat)
        return 0;

    regs = (struct pt_regs *)ctx->args[0];
    pathname = (const char *)regs->si;

    return 0;
}
```