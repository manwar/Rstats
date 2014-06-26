use Test::More 'no_plan';
use strict;
use warnings;

use Rstats;

my $r = Rstats->new;

# log10
{
  # log10 - array reference
  {
    my $a1_values = [2, 3];
    my $a2 = $r->log10($a1_values);
    is_deeply(
      $a2->values,
      [
        log $a1_values->[0] / log 10,
        log $a1_values->[1] / log 10,
      ]
    );
  }

  # log10 - matrix
  {
    my $a1_values = [2, 3];
    my $a2 = $r->log10($r->matrix($a1_values));
    is_deeply(
      $a2->values,
      [
        log $a1_values->[0] / log 10,
        log $a1_values->[1] / log 10,
      ]
    );
    is($a2->type, 'matrix');
  }
}

# log2
{
  # log2 - array reference
  {
    my $a1_values = [2, 3];
    my $a2 = $r->log2($a1_values);
    is_deeply(
      $a2->values,
      [
        log $a1_values->[0] / log 2,
        log $a1_values->[1] / log 2,
      ]
    );
  }

  # log2 - matrix
  {
    my $a1_values = [2, 3];
    my $a2 = $r->log2($r->matrix($a1_values));
    is_deeply(
      $a2->values,
      [
        log $a1_values->[0] / log 2,
        log $a1_values->[1] / log 2,
      ]
    );
    is($a2->type, 'matrix');
  }
}

# log
{
  # log - array reference
  {
    my $a1_values = [2, 3];
    my $a2 = $r->log($a1_values);
    is_deeply(
      $a2->values,
      [
        log $a1_values->[0],
        log $a1_values->[1],
      ]
    );
  }

  # log - matrix
  {
    my $a1_values = [2, 3];
    my $a2 = $r->log($r->matrix($a1_values));
    is_deeply(
      $a2->values,
      [
        log $a1_values->[0],
        log $a1_values->[1],
      ]
    );
    is($a2->type, 'matrix');
  }
}

# expm1
{
  # expm1 - array refference
  {
    my $a1 = $r->expm1([-0.0000005, -4]);
    is_deeply($a1->values, [
      -0.0000005 + 0.5 * -0.0000005 * -0.0000005, exp(-4) - 1.0
    ]);
  }

  # expm1 - matrix
  {
    my $a1 = $r->expm1($r->matrix([-0.0000005, -4]));
    is_deeply($a1->values, [
      -0.0000005 + 0.5 * -0.0000005 * -0.0000005, exp(-4) - 1.0
    ]);
    is($a1->type, 'matrix');
  }
}

# sqrt
{
  # sqrt - array reference
  {
    my $a1_values = [2, 3, 4];
    my $a2 = $r->sqrt($a1_values);
    is_deeply(
      $a2->values,
      [
        sqrt $a1_values->[0],
        sqrt $a1_values->[1],
        sqrt $a1_values->[2]
      ]
    );
  }

  # sqrt - matrix
  {
    my $a1_values = [2, 3, 4];
    my $a2 = $r->sqrt($r->matrix($a1_values));
    is_deeply(
      $a2->values,
      [
        sqrt $a1_values->[0],
        sqrt $a1_values->[1],
        sqrt $a1_values->[2]
      ]
    );
    is($a2->type, 'matrix');
  }
}

# abs
{
  # abs - array refference
  {
    my $a1 = $r->abs([-3, 4]);
    is_deeply($a1->values, [3, 4]);
  }

  # abs - matrix
  {
    my $a1 = $r->abs($r->matrix([-3, 4]));
    is_deeply($a1->values, [3, 4]);
    is($a1->type, 'matrix');
  }
}

# exp
{
  my $v1 = $r->c([2, 3, 4]);
  my $v2 = $r->exp($v1);
  is_deeply(
    $v2->values,
    [
      exp $v1->values->[0],
      exp $v1->values->[1],
      exp $v1->values->[2]
    ]
  );
}

