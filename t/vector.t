use Test::More 'no_plan';
use strict;
use warnings;

use Data::R;
use Data::R::Vector;

# Vector
{
  my $r = Data::R->new;
  
  # add to original vector
  {
    my $v1 = $r->c([1, 2, 3]);
    $v1->set($v1->length + 1 => 6);
    is_deeply($v1->values, [1, 2, 3, 6]);
  }
  
  # append(after option)
  {
    my $v1 = $r->c([1, 2, 3, 4, 5]);
    $v1->append(1, {after => 3});
    is_deeply($v1->values, [1, 2, 3, 1, 4, 5]);
  }

  # append(no after option)
  {
    my $v1 = $r->c([1, 2, 3, 4, 5]);
    $v1->append(1);
    is_deeply($v1->values, [1, 2, 3, 4, 5, 1]);
  }

  # append(array)
  {
    my $v1 = $r->c([1, 2, 3, 4, 5]);
    $v1->append([6, 7]);
    is_deeply($v1->values, [1, 2, 3, 4, 5, 6, 7]);
  }

  # append(vector)
  {
    my $v1 = $r->c([1, 2, 3, 4, 5]);
    $v1->append($r->c([6, 7]));
    is_deeply($v1->values, [1, 2, 3, 4, 5, 6, 7]);
  }
  
  # negation
  {
    my $v1 = $r->c([1, 2, 3]);
    my $v2 = -$v1;
    is_deeply($v2->values, [-1, -2, -3]);
  }
  
  # add
  {
    my $v1 = $r->c([1, 2, 3]);
    my $v2 = $r->c([2, 3, 4]);
    my $v3 = $v1 + $v2;
    is_deeply($v3->values, [3, 5, 7]);
  }

  # add(different element number)
  {
    my $v1 = $r->c([1, 2]);
    my $v2 = $r->c([3, 4, 5, 6]);
    my $v3 = $v1 + $v2;
    is_deeply($v3->values, [4, 6, 6, 8]);
  }
  
  # add(real number)
  {
    my $v1 = $r->c([1, 2, 3]);
    my $v2 = $v1 + 1;
    is_deeply($v2->values, [2, 3, 4]);
  }
  
  # subtract
  {
    my $v1 = $r->c([1, 2, 3]);
    my $v2 = $r->c([3, 3, 3]);
    my $v3 = $v1 - $v2;
    is_deeply($v3->values, [-2, -1, 0]);
  }

  # subtract(real number)
  {
    my $v1 = $r->c([1, 2, 3]);
    my $v2 = $v1 - 1;
    is_deeply($v2->values, [0, 1, 2]);
  }

  # subtract(real number, reverse)
  {
    my $v1 = $r->c([1, 2, 3]);
    my $v2 = 1 - $v1;
    is_deeply($v2->values, [0, -1, -2]);
  }
    
  # mutiply
  {
    my $v1 = $r->c([1, 2, 3]);
    my $v2 = $r->c([2, 3, 4]);
    my $v3 = $v1 * $v2;
    is_deeply($v3->values, [2, 6, 12]);
  }

  # mutiply(real number)
  {
    my $v1 = $r->c([1, 2, 3]);
    my $v2 = $v1 * 2;
    is_deeply($v2->values, [2, 4, 6]);
  }
  
  # divide
  {
    my $v1 = $r->c([6, 3, 12]);
    my $v2 = $r->c([2, 3, 4]);
    my $v3 = $v1 / $v2;
    is_deeply($v3->values, [3, 1, 3]);
  }

  # divide(real number)
  {
    my $v1 = $r->c([2, 4, 6]);
    my $v2 = $v1 / 2;
    is_deeply($v2->values, [1, 2, 3]);
  }

  # divide(real number, reverse)
  {
    my $v1 = $r->c([2, 4, 6]);
    my $v2 = 2 / $v1;
    is_deeply($v2->values, [1, 1/2, 1/3]);
  }
  
  # raise
  {
    my $v1 = $r->c([1, 2, 3]);
    my $v2 = $v1 ** 2;
    is_deeply($v2->values, [1, 4, 9]);
  }
}