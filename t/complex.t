use Test::More 'no_plan';
use strict;
use warnings;

use Data::R;
use Data::R::Complex;

# Complex
{
  my $r = Data::R->new;

  # new
  {
    my $z1 = Data::R::Complex->new(re => 1, im => 2);
    is($z1->re, 1);
    is($z1->im, 2);
  }
  
  # negation
  {
    my $z1 = Data::R::Complex->new(re => 1, im => 2);
    my $z2 = - $z1;
    is($z2->re, -1);
    is($z2->im, -2);
  }
  
  # add
  {
    my $z1 = Data::R::Complex->new(re => 1, im => 2);
    my $z2 = Data::R::Complex->new(re => 3, im => 4);
    my $z3 = $z1 + $z2;
    is($z3->re, 4);
    is($z3->im, 6);
  }
  
  # add(real number)
  {
    my $z1 = Data::R::Complex->new(re => 1, im => 2);
    my $z2 = $z1 + 3;
    is($z2->re, 4);
    is($z2->im, 2);
  }

  # subtract
  {
    my $z1 = Data::R::Complex->new(re => 1, im => 2);
    my $z2 = Data::R::Complex->new(re => 3, im => 4);
    my $z3 = $z1 - $z2;
    is($z3->re, -2);
    is($z3->im, -2);
  }
  
  # subtract(real number)
  {
    my $z1 = Data::R::Complex->new(re => 1, im => 2);
    my $z2 = $z1 - 3;
    is($z2->re, -2);
    is($z2->im, 2);
  }
  
  # subtract(real number, reverse)
  {
    my $z1 = Data::R::Complex->new(re => 1, im => 2);
    my $z2 = 3 - $z1;
    is($z2->re, 2);
    is($z2->im, -2);
  }
  
  # multiply
  {
    my $z1 = 1 + $r->i * 2;
    my $z2 = 3 + $r->i * 4;
    my $z3 = $z1 * $z2;
    is($z3->re, -5);
    is($z3->im, 10);
  }

  # multiply(real number)
  {
    my $z1 = 1 + $r->i * 2;
    my $z2 = $z1 * 3;
    is($z2->re, 3);
    is($z2->im, 6);
  }
  
  # abs
  {
    my $z1 = 3 + $r->i * 4;
    my $abs = $z1->abs;
    is($abs, 5);
  }
  
  # conj
  {
    my $z1 = 1 + $r->i * 2;
    my $conj = $z1->conj;
    is($conj->re, 1);
    is($conj->im, -2);
  }
  
  # divide
  {
    my $z1 = 5 - $r->i * 6;
    my $z2 = 3 + $r->i * 2;
    my $z3 = $z1 / $z2;
    is($z3->re, 3/13);
    is($z3->im, -28/13);
  }

  # divide(real number)
  {
    my $z1 = 2 + $r->i * 4;
    my $z2 = $z1 / 2;
    is($z2->re, 1);
    is($z2->im, 2);
  }

  # divide(real number, reverse)
  {
    my $z1 = 3 + $r->i * 2;
    my $z2 = 5 / $z1;
    is($z2->re, 15 / 13);
    is($z2->im, -10 / 13);
  }

  # raise
  {
    my $z1 = 1 + $r->i * 2;
    my $z2 = $z1 ** 3;
    is($z2->re, -11);
    is($z2->im, -2);
  }
}