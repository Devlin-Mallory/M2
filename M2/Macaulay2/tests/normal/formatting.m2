-- 
R = ZZ [x..z, t_1 .. t_4, s_(1,1) .. s_(2,2), Degrees=>{1,2,3,4,1,2,3, 4: 1}, MonomialOrder=>Lex]
assert (
     toExternalString R == 
     "ZZ[x..z, t_1..t_4, s_(1,1)..s_(2,2), Degrees => {1..4, 1..3, 4:1}, Heft => {1}, MonomialOrder => VerticalList{MonomialSize => 32, Lex => 11, Position => Up}]"
     )

QQ[a][x]
assert( toString (x-a) == "x-a" )
assert( class expression (-a) === Minus )

-- html formatting
debug Core
str = ///A{\it {\bf B}{\tt C\url{D}{\em E}}F}G///
assert(///A<i><b>B</b><span class="tt">C<a href="D">D</a><em>E</em></span>F</i>G/// === html new TEX from str)
assert(///<span class="tt">A<em>B</em>C</span>/// === html TEX{"{\\tt A", EM{"B"}, "C}"})
assert Equation(urlEncode "https://en.wikipedia.org/wiki/Gröbner basis",
    "https://en.wikipedia.org/wiki/Gr%C3%B6bner%20basis")
