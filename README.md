# uwufy
A program to 'uwufy' different text.
The program is a c++ clone of [uwu](https://git.sr.ht/~polanco/uwu)

## Usage
Here is a basic example.
<pre><font color="#4E9A06"><b>$</b></font> uwufy &quot;The train is late&quot;
De twain is wate</pre>
The program also supports reading files.
<pre><font color="#4E9A06"><b>$</b></font> echo &quot;The train is long.&quot; &gt; test.txt
<font color="#4E9A06"><b>$</b></font> uwufy -f ./test.txt 
De twain is wong.</pre>
The program also supports piping. Here is an example were I use the [fotune](https://github.com/shlomif/fortune-mod) program.
<pre><font color="#4E9A06"><b>$</b></font> fortune | uwufy
&quot;To take a significant step fowwawd, yuw must make a sewies of finite
impwovements.&quot;
		-- Donawd J. Atwood, Genewaw Motows</pre>
## License
The program is licensed under the [MIT license](https://opensource.org/licenses/MIT).