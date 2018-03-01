

all: prob

prob:
	g++ -O3 prob.cpp -o prob

a: prob
	./prob < a_example.in > a.out

b: prob
	./prob < b_should_be_easy.in > b.out

c: prob
	./prob < c_no_hurry.in > c.out

d: prob
	./prob < d_metropolis.in > d.out

e: prob
	./prob < e_high_bonus.in > e.out