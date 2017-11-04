Run examples with `./run-examples.sh N` where `N` is the number of the script.  

**script-0.rnbw**  

The simplest example is just list the color numbers.  

```
--width  2     
--angle  60    
--colors 196, 202, 208, 214, 220   
```
![](https://user-images.githubusercontent.com/22116479/32402021-f3596bb0-c123-11e7-9e37-d4c3c4eb6215.png)

**script-1.rnbw**  

Notice that the same result can be achieved with the following script.  

```
--path   line
--width  2
--angle  60
--colors 196->220
```
![](https://user-images.githubusercontent.com/22116479/32402020-f3403fb4-c123-11e7-95da-d0e416a630c5.png)
  
**script-2.rnbw**  

Notice `<->`. It makes colors go from 33 to 158 and then back to 33 (not including the last 33).
Also notice changes in `--width` and `--angle` option.  

```
--path   edges rgb
--width  3
--angle  0
--colors 33<->158
```
![](https://user-images.githubusercontent.com/22116479/32402019-f3279a68-c123-11e7-9d36-b7c98f4274e9.png)

**script-3.rnbw**  

Notice how you can use `()` to indicate color on a side of an interval as not included.  
Opposed to `[]` which indicate that color should be included.  
The `[]` behaviour is the default one.  

```
--path   edges rgb
--width  2
--angle  110
--colors [33->158], (158->22], (22->44], (44->33)
```
![](https://user-images.githubusercontent.com/22116479/32402018-f30d32fe-c123-11e7-9064-b6ed20ae7f7f.png)

**script-4.rnbw**  

Notice `rgb`.  

```
--path   edges rgb
--width  2
--angle  15
--colors 16->231
```
![](https://user-images.githubusercontent.com/22116479/32402017-f2f3f67c-c123-11e7-99da-712c791fb6ad.png)

**script-5.rnbw**  

Notice that `rgb` is changed to `rbg`.  

```
--path   edges rbg
--width  2
--angle  15
--colors 16->231
```
![](https://user-images.githubusercontent.com/22116479/32402016-f2dafcda-c123-11e7-9d57-fb2b46ed7dc1.png)

**script-6.rnbw**  

Notice `gbr`.  

```
--path   edges gbr
--width  2
--angle  15
--colors 16->231
```
![](https://user-images.githubusercontent.com/22116479/32402015-f2c21134-c123-11e7-97da-d0e1b7675ce8.png)

**script-7.rnbw**  

Notice that `--path` is changed to `line` sort and how it affected the output.  

```
--path   line
--width  2
--angle  15
--colors 16->231
```
![](https://user-images.githubusercontent.com/22116479/32402014-f2a622b2-c123-11e7-9744-f0d512858e11.png)

**script-8.rnbw**  

Notice how `--colors` option is affected by the previous `--path` option. You get 5 different stripes.  

```
--width  1
--angle  90

--path   edges rgb
--colors 53->231

--path   edges rbg
--colors 53->231

--path   edges brg
--colors 53->231

--path   edges gbr
--colors 53->231

--path   edges bgr
--colors 53->231
```
![](https://user-images.githubusercontent.com/22116479/32408473-018e16cc-c1a1-11e7-8258-5497e2f09b12.png)

**script-9.rnbw**  

Notice how beautiful it can get.  

```
--path   edges grb
--colors [82->87], (87->120], (120->213], (213->82]
```

![](https://user-images.githubusercontent.com/22116479/32408542-49af48b2-c1a2-11e7-9579-ba5389b047fc.png)

**script-10.rnbw**

Notice how you can use verbose `from to` syntax combined with color names instead of color numbers and get the same result.  

```
--path   edges grb
--colors from chartreuse-2a to dark-slate-gray,
         from not including dark-slate-gray to light-green-3,
         from not including light-green-3 to orchid-1,
         from not including orchid-1 to not including chartreuse-2a
```

![](https://user-images.githubusercontent.com/22116479/32408585-2fb972c4-c1a3-11e7-838e-767d602c722f.png)



