use Test::More 'no_plan';
use strict;
use warnings;

use Rstats::Class;
use Rstats::ArrayFunc;

my $r = Rstats::Class->new;

# comparison operator
{
  # comparison operator - ==, true
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $ret = Rstats::ArrayFunc::equal($z1, $z2);
    is($ret->value, 1);
  }
  # comparison operator - ==, false
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 1, im => 1});
    my $ret = Rstats::ArrayFunc::equal($z1, $z2);
    is($ret->value, 0);
  }

  # comparison operator - !=, true
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    is(Rstats::ArrayFunc::not_equal($z1, $z2)->value, 0);
  }
  
  # comparison operator - !=, false
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 1, im => 1});
    is(Rstats::ArrayFunc::not_equal($z1, $z2)->value, 1);
  }

  # comparison operator - <, error
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    eval { my $result = Rstats::ArrayFunc::less_than($z1, $z2) };
    like($@, qr/invalid/);
  }

  # comparison operator - <=, error
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    eval { my $result = Rstats::ArrayFunc::less_than_or_equal($z1, $z2) };
    like($@, qr/invalid/);
  }

  # comparison operator - >, error
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    eval { my $result = Rstats::ArrayFunc::more_than($z1, $z2) };
    like($@, qr/invalid/);
  }

  # comparison operator - >=, error
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    eval { my $result = Rstats::ArrayFunc::more_than_or_equal($z1, $z2) };
    like($@, qr/invalid/);
  }
}

# to_string
{
  # to_string - basic
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    is("$z1", "1+2i");
  }
  
  # to_string - image number is 0
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 0});
    is("$z1", "1+0i");
  }
  
  # to_string - image number is minus
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => -1});
    is("$z1", "1-1i");
  }
}

# new
{
  # new
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    is($z1->value->{re}, 1);
    is($z1->value->{im}, 2);
  }
}

# operation
{
  # operation - negation
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::negation($z1);
    is($z2->value->{re}, -1);
    is($z2->value->{im}, -2);
  }
  
  # operation - add
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 3, im => 4});
    my $z3 = Rstats::ArrayFunc::add($z1, $z2);
    is($z3->value->{re}, 4);
    is($z3->value->{im}, 6);
  }
  
  # operation - subtract
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 3, im => 4});
    my $z3 = Rstats::ArrayFunc::subtract($z1, $z2);
    is($z3->value->{re}, -2);
    is($z3->value->{im}, -2);
  }
  
  # operation - multiply
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 3, im => 4});
    my $z3 = Rstats::ArrayFunc::multiply($z1, $z2);
    is($z3->value->{re}, -5);
    is($z3->value->{im}, 10);
  }

  # operation - abs
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 3, im => 4});
    my $abs = Rstats::ArrayFunc::abs($z1);
    is($abs->value, 5);
  }
  
  # operation - Conj
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $conj = Rstats::ArrayFunc::Conj($z1);
    is($conj->value->{re}, 1);
    is($conj->value->{im}, -2);
  }
  
  # operation - divide
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 5, im => -6});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 3, im => 2});
    my $z3 = Rstats::ArrayFunc::divide($z1, $z2);
    is($z3->value->{re}, 3/13);
    is($z3->value->{im}, -28/13);
  }

  # operation - pow
  {
    my $z1 = Rstats::ArrayFunc::new_complex({re => 1, im => 2});
    my $z2 = Rstats::ArrayFunc::new_complex({re => 3, im => 0});
    my $z3 = Rstats::ArrayFunc::pow($z1, $z2);
    is($z3->value->{re}, -11);
    is($z3->value->{im}, -2);
  }
}
