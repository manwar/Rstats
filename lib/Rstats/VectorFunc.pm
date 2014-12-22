package Rstats::VectorFunc;

use strict;
use warnings;
use Carp 'croak', 'carp';

require Rstats;
use Rstats::Vector;
use Math::Trig ();

sub TRUE () { new_true() }
sub FALSE () { new_false() }
sub NA () { new_na() }
sub NaN () { new_nan() }
sub Inf () { new_inf() }
sub negativeInf () { new_negative_inf() }
sub pi () { new_double(Math::Trig::pi) }

sub new_vector {
  my $type = shift;
  
  if ($type eq 'character') {
    return new_character(@_);
  }
  elsif ($type eq 'complex') {
    return new_complex(@_);
  }
  elsif ($type eq 'double') {
    return new_double(@_);
  }
  elsif ($type eq 'integer') {
    return new_integer(@_);
  }
  elsif ($type eq 'logical') {
    return new_logical(@_);
  }
  else {
    croak("Invalid type $type is passed(new_vector)");
  }
}

sub atanh {
  my $e1 = shift;
  
  return $e1 if $e1->is_na->value;
  
  my $e2;
  if ($e1->is_complex) {
    if (equal($e1, new_complex({re => 1, im => 0}))->value) {
      $e2 = complex_double(Inf, NaN);
      carp("In atanh() : NaNs produced");
    }
    elsif (equal($e1, new_complex({re => -1, im => 0}))->value) {
      $e2 = complex_double(negativeInf, NaN);
      carp("In atanh() : NaNs produced");
    }
    else {
      $e2 = multiply(
        new_complex({re => 0.5, im => 0}),
        Rstats::VectorFunc::log(
          divide(
            add(new_complex({re => 1, im => 0}), $e1),
            subtract(new_complex({re => 1, im => 0}), $e1)
          )
        )
      );
    }
  }
  elsif ($e1->is_numeric || $e1->is_logical) {
    $e1 = $e1->as_double;
    return $e1 if $e1->is_nan->value;
    
    if ($e1->is_infinite->value) {
        $e2 = NaN;
        carp "In acosh() : NaNs produced";
    }
    else {
      if (equal($e1, new_double(1))->value) {
        $e2 = Inf;
      }
      elsif (equal($e1, new_double(-1))->value) {
        $e2 = negativeInf;
      }
      elsif (less_than(Rstats::VectorFunc::abs($e1), new_double(1))->value) {
        $e2 = divide(
          Rstats::VectorFunc::log(
            divide(
              add(new_double(1), $e1),
              subtract(new_double(1), $e1)
            )
          ),
          new_double(2)
        );
      }
      else {
        $e2 = NaN;
        carp "In acosh() : NaNs produced";
      }
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub acosh {
  my $e1 = shift;
  
  return $e1 if $e1->is_na->value;
  
  my $e2;
  if ($e1->is_complex) {
    my $e1_re = Rstats::VectorFunc::new_double($e1->value->{re});
    my $e1_im = Rstats::VectorFunc::new_double($e1->value->{im});

    my $e2_t = add(
      Rstats::VectorFunc::sqrt(
        subtract(
          multiply($e1, $e1),
          new_complex({re => 1, im => 0})
        ),
      ),
      $e1
    );
    my $e2_u = Rstats::VectorFunc::log($e2_t);
    my $e2_re = Re($e2_u);
    my $e2_im = Im($e2_u);
    
    if (less_than($e1_re, new_double(0))->value && equal($e1_im, new_double(0))->value) {
      $e2 = complex_double($e2_re, negation($e2_im));
    }
    else {
      $e2 = complex_double($e2_re, $e2_im);
    }
    
    if (less_than($e1_re, new_double(0))->value) {
      $e2 = negation($e2);
    }
  }
  elsif ($e1->is_numeric || $e1->is_logical) {
    $e1 = $e1->as_double;
    return $e1 if $e1->is_nan->value;
    
    if ($e1->is_infinite->value) {
        $e2 = NaN;
        carp "In acosh() : NaNs produced";
    }
    else {
      if (more_than_or_equal($e1, new_double(1))->value) {
        $e2 = Rstats::VectorFunc::log(
          add(
            $e1,
            Rstats::VectorFunc::sqrt(
              subtract(
                multiply($e1, $e1),
                new_double(1)
              )
            )
          )
        );
      }
      else {
        $e2 = NaN;
        carp "In acosh() : NaNs produced";
      }
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub asinh {
  my $e1 = shift;
  
  return $e1 if $e1->is_na->value;
  
  my $e2;
  if ($e1->is_complex) {
  
    my $e2_t = add(
      Rstats::VectorFunc::sqrt(
        add(
          multiply($e1, $e1),
          new_complex({re => 1, im => 0})
        )
      ),
      $e1
    );
    
    $e2 = Rstats::VectorFunc::log($e2_t);
  }
  elsif ($e1->is_numeric || $e1->is_logical) {
    $e1 = $e1->as_double;
    return $e1 if $e1->is_nan->value;
    
    if ($e1->is_positive_infinite->value) {
      $e2 = Inf;
    }
    elsif ($e1->is_negative_infinite->value) {
      $e2 = negativeInf;
    }
    else {
      my $e2_t = add(
        $e1,
        Rstats::VectorFunc::sqrt(
          add(
            multiply($e1, $e1),
            new_double(1)
          )
        )
      );
      
      $e2 = Rstats::VectorFunc::log($e2_t);
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub atan {
  my $e1 = shift;
  
  return $e1 if $e1->is_na->value;
  
  my $e2;
  if ($e1->is_complex) {
    
    if (equal($e1, new_complex({re => 0, im => 0}))->value) {
      $e2 = new_complex({re => 0, im => 0});
    }
    elsif (equal($e1, new_complex({re => 0, im => 1}))->value) {
      $e2 = complex_double(new_double(0), Inf);
    }
    elsif (equal($e1, new_complex({re => 0, im => -1}))->value) {
      $e2 = complex_double(new_double(0), negativeInf);
    }
    else {
      my $e2_i = new_complex({re => 0, im => 1});
      my $e2_log = Rstats::VectorFunc::log(
        divide(
          add($e2_i, $e1),
          subtract($e2_i, $e1)
        )
      );
      
      $e2 = multiply(
        divide($e2_i, new_complex({re => 2, im => 0})),
        $e2_log
      );
    }
  }
  elsif ($e1->is_numeric || $e1->is_logical) {
    $e2 = Rstats::VectorFunc::atan2($e1->as_double, new_double(1));
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub hash {
  my $e1 = shift;
  
  my $hash = $e1->type . '-' . "$e1";
  
  return $hash;
}

sub acos {
  my $e1 = shift;

  return $e1 if $e1->is_na->value;
  
  my $e2;
  if ($e1->is_complex) {

    my $e1_re = Rstats::VectorFunc::new_double($e1->value->{re});
    my $e1_im = Rstats::VectorFunc::new_double($e1->value->{im});
    
    if (equal($e1_re, new_double(1))->value && equal($e1_im, new_double(0))->value) {
      $e2 = new_complex({re => 0, im => 0});
    }
    else {
      my $e2_t1 = Rstats::VectorFunc::sqrt(
        add(
          multiply(
            add($e1_re, new_double(1)),
            add($e1_re, new_double(1))
          ),
          multiply($e1_im, $e1_im)
        )
      );
      my $e2_t2 = Rstats::VectorFunc::sqrt(
        add(
          multiply(
            subtract($e1_re, new_double(1)),
            subtract($e1_re, new_double(1))
          ),
          multiply($e1_im, $e1_im)
        )
      );
      
      my $e2_alpha = divide(
        add($e2_t1,  $e2_t2),
        new_double(2)
      );
      
      my $e2_beta  = divide(
        subtract($e2_t1, $e2_t2),
        new_double(2)
      );
      
      if (less_than($e2_alpha, new_double(1))->value) {
        $e2_alpha = new_double(1);
      }
      
      if (more_than($e2_beta, new_double(1))->value) {
        $e2_beta =  new_double(1);
      }
      elsif (less_than($e2_beta, new_double(-1))->value) {
        $e2_beta = new_double(-1);
      }
      
      my $e2_u =  Rstats::VectorFunc::atan2(
        Rstats::VectorFunc::sqrt(
          subtract(
            new_double(1),
            multiply($e2_beta, $e2_beta)
          )
        ),
        $e2_beta
      );
      
      my $e2_v = Rstats::VectorFunc::log(
        add(
          $e2_alpha,
          Rstats::VectorFunc::sqrt(
            subtract(
              multiply($e2_alpha, $e2_alpha),
              new_double(1)
            )
          )
        )
      );
      
      if (more_than($e1_im, new_double(0))->value || (equal($e1_im, new_double(0))->value && less_than($e1_re, new_double(-1))->value)) {
        $e2_v = negation($e2_v);
      }
      
      $e2 = complex_double($e2_u, $e2_v);
    }
  }
  elsif ($e1->is_numeric || $e1->is_logical) {
    if ($e1->is_infinite->value) {
      carp "In sin : NaNs produced";
      $e2 = NaN;
    }
    elsif ($e1->is_nan->value) {
      $e2 = $e1;
    }
    else {
      $e1 = $e1->as_double;
      if (less_than_or_equal(Rstats::VectorFunc::abs($e1), new_double(1))->value) {
        $e2 = Rstats::VectorFunc::atan2(
          Rstats::VectorFunc::sqrt(
            subtract(
              new_double(1),
              multiply($e1, $e1)
            )
          ),
          $e1
        );
      }
      else {
        carp 'In asin : NaNs produced';
        $e2 = NaN;
      }
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub asin {
  my $e1 = shift;

  return $e1 if $e1->is_na->value;
  
  my $e2;
  if ($e1->is_complex) {

    my $e1_re = Rstats::VectorFunc::new_double($e1->value->{re});
    my $e1_im = Rstats::VectorFunc::new_double($e1->value->{im});
    
    if (equal($e1_re, new_double(0))->value && equal($e1_im, new_double(0))->value) {
      $e2 = new_complex({re => 0, im => 0});
    }
    else {
      my $e2_t1 = Rstats::VectorFunc::sqrt(
        add(
          multiply(
            add($e1_re, new_double(1)),
            add($e1_re, new_double(1))
          ),
          multiply($e1_im, $e1_im)
        )
      );
      my $e2_t2 = Rstats::VectorFunc::sqrt(
        add(
          multiply(
            subtract($e1_re, new_double(1)),
            subtract($e1_re, new_double(1))
          ),
          multiply($e1_im, $e1_im)
        )
      );
      
      my $e2_alpha = divide(
        add($e2_t1,  $e2_t2),
        new_double(2)
      );
      
      my $e2_beta  = divide(
        subtract($e2_t1, $e2_t2),
        new_double(2)
      );
      
      if (less_than($e2_alpha, new_double(1))->value) {
        $e2_alpha = new_double(1);
      }
      
      if (more_than($e2_beta, new_double(1))->value) {
        $e2_beta =  new_double(1);
      }
      elsif (less_than($e2_beta, new_double(-1))->value) {
        $e2_beta = new_double(-1);
      }
      
      my $e2_u =  Rstats::VectorFunc::atan2(
        $e2_beta,
        Rstats::VectorFunc::sqrt(
          subtract(
            new_double(1),
            multiply($e2_beta, $e2_beta)
          )
        )
      );
      
      my $e2_v = negation(
        Rstats::VectorFunc::log(
          add(
            $e2_alpha,
            Rstats::VectorFunc::sqrt(
              subtract(
                multiply($e2_alpha, $e2_alpha),
                new_double(1)
              )
            )
          )
        )
      );
      
      if (more_than($e1_im, new_double(0))->value || (equal($e1_im, new_double(0))->value && less_than($e1_re, new_double(-1))->value)) {
        $e2_v = negation($e2_v);
      }
      
      $e2 = complex_double($e2_u, $e2_v);
    }
  }
  elsif ($e1->is_numeric || $e1->is_logical) {
    if ($e1->is_infinite->value) {
      carp "In sin : NaNs produced";
      $e2 = NaN;
    }
    elsif ($e1->is_nan->value) {
      $e2 = $e1;
    }
    else {
      $e1 = $e1->as_double;
      if (less_than_or_equal(Rstats::VectorFunc::abs($e1), new_double(1))->value) {
        $e2 = Rstats::VectorFunc::atan2(
          $e1,
          Rstats::VectorFunc::sqrt(
            subtract(
              new_double(1),
              multiply($e1, $e1)
            )
          )
        );
      }
      else {
        carp 'In asin : NaNs produced';
        $e2 = NaN;
      }
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub create {
  my ($type, $value) = @_;
  
  $value = 0 unless defined $value;

  if ($type eq 'character') {
    return character("$value");
  }
  elsif ($type eq 'complex') {
    return new_complex({re => $value, im => 0});
  }
  elsif ($type eq 'double') {
    return new_double($value);
  }
  elsif ($type eq 'integer') {
    return new_integer($value);
  }
  elsif ($type eq 'logical') {
    return new_logical($value ? Rstats::VectorFunc::TRUE : Rstats::VectorFunc::FALSE);
  }
  else {
    croak 'Invalid type';
  }
}

sub Mod { Rstats::VectorFunc::abs(@_) }

=head1 NAME

Rstats::VectorFunc - Vector functions

1;
