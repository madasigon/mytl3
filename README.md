# mytl3
Generic implementation of algorithms that are often used at programming competitions


mytl3 is a collection of C++17 implementations of commonly used algorithms for competitive programming.
It tries to be as generic as possible. For this it uses C++ templates.
For example the implementation of the [Segment Tree](https://en.wikipedia.org/wiki/Segment_tree) has a template argument to specify the type of the elements and the corresponding operations on them.
This means you can have a Segment Tree for querying the
* greatest common divisor of elements
* sum of elements
* maximum/minimum of elements
* or something very abstract like the number of mutually exclusive intervals

over arbitrary ranges by really only writing 2 or 3 lines of code in a template class.

I also try to make it as hard to make bugs with the library as possible. For example I made a *Modulo* class to make calculations modulo a number *MOD* which is known at compile time.
I made it so that if you want to cast a *Modulo* value to an *int*, you have to do so explicitly, otherise it would be dangerous.

In competitive programming, people have to write efficient code in little time, at the expense of safety.
This also means that unfortunately this "library" is often too slow because it usually has a big "constant factor".
Nevertheless, making these implementations has helped me gain a "safer coding/thinking style" which I can employ even when not actually using this "library".
