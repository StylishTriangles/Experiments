# Usage
`make`

`make test`

# Example results

```
         Switch  |  IfElse | Chksum
-----------------+---------+--------
-O2                              
-----------------+---------+--------
Cyclic:  2.41361 | 2.58248 | 818256
Random:  6.46729 | 5.84790 | 841816
Default: 2.36937 | 2.96184 | 202925
-----------------+---------+--------
-O3                              
-----------------+---------+--------
Cyclic:  2.42242 | 2.62853 | 818256
Random:  6.60602 | 6.04727 | 841816
Default: 2.40982 | 2.94818 | 202925
-----------------+---------+--------
-O3 -flto -fuse-linker-plugin -march=native
-----------------+---------+--------
Cyclic:  0.66503 | 0.59515 | 818256
Random:  4.47605 | 3.89285 | 841816
Default: 0.61899 | 0.90835 | 202925
```

# Comment
Running this test multiple times seems to provide similar results.
Switch/case in the first two optimization cases performed slightly better. 
The exception was "random" test which would pick a random case fooling branch predictor in the process. Here If/Else was faster probably because of the shorter machine code.

What's surprising at first is the result from final competitor -flto (link time optimization) It managed to execute about 4 times faster than previous tests. By looking into the compiled code we can see that this is in fact due to inlining `fun` and `fun2` therefore wasting no time on calls.

# Addendum
This was tested with seemingly random cases in the switch.
It's worth noting that if the values present in switch statement are in an easily predictable sequence (ex. 3,4,5,6,7,8) the compiler is able to do some extra magic and the switch/case test would win by a large margin.

TL;DR Use switch/case kids