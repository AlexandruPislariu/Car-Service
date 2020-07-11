# Car-Service
Object Oriented Project in C++
~
Concepts used:
Inheritance
Polimorphism
Abstract Classes and Pur Virtual methods
Overloading operators (<<, ==, +, etc.)
Overriding methods (I created and abstract Repository, and two repos RepositoryFile and RepositoryMemory which override pur virtual mehods from RepositoryAbstract)
Smart pointers (to create an Undo environment I had to use unique_ptr, because my Undo class is abstract and can't be iterate)
GUI (I used Qt to create a graphic user interface with buttons, text boxes and so on)
Observer (to syncronize multiple QWidgets)
AbstractTableModel (to create my table model)
~

