-------- First I would like to explain the thought process of the program. --------

The world list was downloaded off of github (credits posted in main function located in hangman2.cpp).
From this, I decided to write an extra program titled filter.cpp to read dict.txt and filter out the 
shorter words (I decided that words less than 3 letters would be discarded). filter.cpp would take
dict.txt, process it, and write an output in filtered.txt. 

Since vectors were forbidden in the main program, Hangman version two, I decided to write my own 
"vector" functions, hence, dynamic.cpp. The two most important functions in dynamic.cpp are init_char()
and append_char(). These were aimed to replicate initiating a vector<char> of size 1 and the operator
vector.push_back(). The entire program was then built off of storing and accessing the pointers provided
by the two functions. 

-------- I have a few questions regarding mem allocation and I would greatly appreciate
if you could include the answers in the comments --------

After I finish using the memory, I should delete the memory as such:

    delete[] ptrToStartArr;

This should tell the system OS to mark the memory as "free" right?

If this is the case, then how am I still able to access the memory by using the same pointer?

Other times. The program seems to re-allocate the same block of memory that has been previously deleted
(through the function init_char()).

This would cause undesired operations. This was why I took out the "play" again functionality in
this second iteration. Do you have any clue on why this happens?


-------- Response to Questions --------

1.  Why did you select the project you did?

I choose to redo hangman because I thought it would best test my knowledge regarding pointers and 
dynamic memory. Furthermore, after comparing hangman and mastermind, I figured that hangman would
also give me more opportunities. Mainly, hangman needed dynamic memory (vectors) to function properly.
This was a huge challenge given the fact that I had no previous knowledge about pointers despite knowing
a little bit of C++ before coming into this class. It took a lot of debugging to get the program to work
the way it does now. 

2.  Do you prefer using elements such as a vector<t> or doing memory management "from scratch"?  Why?

After this week's handicap, not being able to use std::vector<T>, I have newfound respect for the
STL. Vectors make programming a whole lot easier because it allows me to worry about other things and not
pointers, array size, allocating, deallocating, and accessing memory. This is why I prefer using std::vector<T>
over memory management from scratch.
