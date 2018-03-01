
SOURCE=good_b.cpp

all: prob

prob: ${SOURCE}
	g++ --std=c++11 -O3 ${SOURCE} -o prob

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