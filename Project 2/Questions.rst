PS2 Questions
=============

Add your answers to this file in plain text after each question.  Leave a blank line between the text of the question and the text of your answer and at least two lines between your answer and the next question.

.. role:: cpp(code)
   :language: c++


Inner Product
-------------

1. How would you use :cpp:`dot` to implement :cpp:`two_norm`?

|
Since the :cpp:`two_norm` is calculated by taking the square root of the sum of each vector element squared, and :cpp:`dot` calculates the dot product of two vector. Since the sum of each vector element squared is the same concept as taking the dot product of two same vectors, so we can have the :cpp:`dot` function take two exact x vectors, then we simply take square root of the result we get from the :cpp:`dot` function, and that is the :cpp:`two_norm` we want to get. 

|
Tensors
-------

2. What is the formula that we would use for indexing if we wanted "slab-major" ordering?  Hint:  What is the size of a slab?  It might be helpful to draw a picture of the data in 3D and see what the size is of a slab.

|
We represent the position of an element in a 3 dimensional space as A(i, j, k). e.g. (slab, row, column) Suppose we have L slabs, M rows, and N columns. The indexing formula is: [k + M * (j + L * i)]. 

|

3. (Extra credit.) I claim that there are six distinct indexing formulas.  Show that this claim is correct or that it is incorrect.

|
Yes, this claim is correct.

Since for a 3D space, we can have the index (i, j, k) represent:

1. (slab, row, column) 2. (slab, column, row) 3. (row, slab, column)

4. (row, column, slab) 5.(column, slab, row)  6. (column, row, slab)

We can get the following indexing formulas corresponding with the six options we just listed: 

1. [k + M * (j + L * i)] 2. [j + M * (k + L * i)] 3. [k + M * (i + L * j)]

4. [j + M * (i + L * k)] 5. [i + M * (k + L * j)] 6. [i + M * (j + L * k)].
