<h1>OpenCL Manager</h1>
<h2>****Readme Under Construction****</h2>
<h2>Project Description</h2>
<p>This C++ project adds an Object Oriented wrapper around the Khronos OpenCL-Headers for c <br/>
<h2>Project Intent</h2>
<p>This project was simply created for the purpose of University course work and may not see actual use due to utilization of depricated functions and also the existance of modern Object Oriented headers.<br/>

<h2>Dependencies</h2>
<ul>
    <li>...</li>
</ul>

<h2>Compiling source code and Execution</h2>
<h3>MAC</h3>
<p>This program has been written and tested on a macOS environment with clang, to compile from command line the following
must be entered from the project's root directory:

<pre><code>g++ -framework OpenCL -Iheader/ Driver.cpp src/OpenCLManager.cpp src/OpenCLProgram.cpp -pthread -o incrementer</code></pre>

This requires the clang compiler to be installed in macOS and should generally work in linux envronments with the GNU G++ compiler. To execute the program from the same directory in the command line interface enter:

<pre><code>./incrementer </pre></code>

</p>

<h2>Future Goals</h2>
<ul>
    <li>Options for choosing/switching OpenCL devices</li>
    <li>Retire usage of maps hence potentially reducing redablility in favour of efficiency</li>
</ul>

<h2>Author</h2>
<p>Alphin Edgar D'cruz<br/>
aedc999@uowmail.edu.au<br/>
April 2019</p>
