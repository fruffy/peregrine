## Prompt
"""
You are given a DSL with BNF notation and asked to complete some tasks. For whatever tasks, you will strictly follow the notation and use the DSL to answer.

The rules:
<program> ::= <expression> | <expression> <program>
<expression> ::= <term> | <term> <make-sound> | <term> <logical-op> <expression>
<term> ::= <animal>
<make-sound> ::= <animal> "(" <sound> ")"
<animal> ::= "cat" | "dog" | "cow" | "pig"
<sound> ::= "meow" | "woof" | "moo" | "oink"
<logical-op> ::= "AND" | "OR" | "XOR" | "NOR"
"""

[All prompts start with: Give me a expression that meets the following conditions]
1. an animal makes a sound
\\
GPT 3: `dog(woof)`
\\
GPT 4: `cat(meow)`

2. two animals of same kind don't make sounds and one animal of different kind makes a sound
\\
GPT 3: `cat AND cat NOR dog AND dog XOR pig("meow")`
\\
GPT 4: `cat cat dog(woof)`

3. an animal that makes a sound or two animals of different kind than the first one that don't make a sound
\\
GPT 3: `<animal>("meow") OR <animal> NOR <animal>`
\\
GPT 4: `cat(meow) OR dog pig`

4. an animal that makes a sound and two animals of same kind but different from the first one make same sounds
\\
GPT 3: `<animal>("meow") AND <animal>("meow") AND <animal>("meow")`
\\
GPT 4: `cat(meow) AND dog(woof) dog(woof)`

5. an animal that makes a sound and another animal of different kind makes the same sound as the first animal
\\
GPT 3: `<animal>("meow") AND <animal>("meow")`
\\
GPT 4: I'm sorry, but according to the provided DSL, it is not possible for two animals of different kinds to make the same sound. Each `<animal>` has a specific `<sound>` associated with it, as defined by the `<sound>` rule. For example, a "cat" can only make the sound "meow" and a "dog" can only make the sound "woof". Is there anything else you would like to know?

6. two animals of kind A and one animal of kind B or three animals of kind A that makes three different sounds
\\
GPT 3: `(cat AND cat) OR (cat AND dog AND cow)`

7. two animals, none make a sound
\\
GPT 3: `<animal> AND <animal>`
\\
GPT 4: `cat dog`