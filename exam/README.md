This folder contains my solutions to the **exam project**. The main solution is found in **main.c**
which is the framework of the project. The remainding files are the implemented methods with corresponding header files,
as well as a **Makefile.**  The actual solution output can be viewed in **output.txt** which formally contains my **answer** (solution) to the problem.

My student number is 201708238, and so my given project number is
38 % 22 = 16.

**16: Adaptive recursive integrator with subdivision into three subintervals**
Implement a (one-dimensional) adaptive recursive integrator (open or closed
quadrature, at your choice) which at each iteration subdivides the interval not
into two, but into three sub-intervals. Reuse points. Compare with the adaptive
integrator from your homework.


**Solution outline**

In the adaptive quadrature algorithm the integration interval is
subdivided into adaptive subintervals. For this project, the number of subintervals is 3

One needs to choose the points **x_i** to be evenly spaced in the intervals

			    x_i = {1/6, 3/6, 5/6}.

With **w_i**  from the trapezium rule

	  [[   1        1        1    ]      [[ w_1 ]      [[  1  ]
	   [  x_1      x_2      x_3   ]   *   [ w_2 ]   =   [ 1/2 ]   ,
	   [  x_1^2    x_2^2    x_3^2 ]]      [ w_3 ]]      [ 1/3 ]]

which will give

			    w_i = {3/8, 2/8, 3/8},

along with **v_i** from the rectangle rule

			    v_i = {1/3, 1/3, 1/3}.


