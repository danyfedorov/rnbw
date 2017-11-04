# `R N B W`
  
Inspired by lolcat.  

WIP

### Examples
`$ ./examples/generate-text.sh | ./rnbw -c from 144 to 42, from 42 to 83, from 83 to 219, from 219 to not including 144`
![](https://user-images.githubusercontent.com/22116479/32402606-98d1647e-c130-11e7-9558-a5501df6fc79.png)

TODO: more

See more at [examples/README.md](https://github.com/bugdie4k/rnbw/tree/master/examples/README.md)

### Syntax 

TODO

### Building

**Dependencies:**  
 
`antlr3.2`       - If you want to generate lexer and parser files yourself. You can find generated files in the `grammar` directory.  
`libantlr3c-dev` - ANTLR C runtime.  
`libutfcpp-dev`  - Provides UTF-8 support.  

**Run:**  
`make grammar` - To generate lexer and parser files from grammar.  
`make app`     - To build a program.  


