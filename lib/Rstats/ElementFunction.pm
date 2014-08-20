package Rstats::ElementFunction;

use strict;
use warnings;
use Carp 'croak', 'carp';

require Rstats::Element::NA;
require Rstats::Element::Logical;
require Rstats::Element::Complex;
require Rstats::Element::Character;
require Rstats::Element::Integer;
require Rstats::Element::Double;
use Scalar::Util ();
use B ();
use Math::Complex ();
use POSIX ();
use Math::Trig ();

# Perl infinite values(this is value is only valid as return value)
my $perl_inf_result = 9 ** 9 ** 9;
my $perl_negative_inf_result = -9 ** 9 ** 9;

# Special values
my $na = Rstats::Element::NA->new;
my $nan = Rstats::Element::Double->new(flag => 'nan');
my $inf = Rstats::Element::Double->new(flag => 'inf');
my $negative_inf = Rstats::Element::Double->new(flag => '-inf');
my $true = logical(1);
my $false = logical(0);
my $pi = double(Math::Trig::pi);

# Address
my $true_ad = Scalar::Util::refaddr $true;
my $false_ad = Scalar::Util::refaddr $false;
my $na_ad = Scalar::Util::refaddr $na;
my $nan_ad = Scalar::Util::refaddr $nan;
my $inf_ad = Scalar::Util::refaddr $inf;
my $negative_inf_ad = Scalar::Util::refaddr $negative_inf;

sub TRUE () { $true }
sub FALSE () { $false }
sub NA () { $na }
sub NaN () { $nan }
sub Inf () { $inf }
sub negativeInf () { $negative_inf }
sub pi () { $pi }

sub is_nan ($) { ref $_[0] && (Scalar::Util::refaddr $_[0] == $nan_ad) }
sub is_na ($) { ref $_[0] && (Scalar::Util::refaddr $_[0] == $na_ad) }
sub is_infinite ($) { is_positive_infinite($_[0]) || is_negative_infinite($_[0]) }
sub is_positive_infinite ($) { ref $_[0] && (Scalar::Util::refaddr $_[0] == $inf_ad) }
sub is_negative_infinite ($) { ref $_[0] && (Scalar::Util::refaddr $_[0] == $negative_inf_ad) }
sub is_finite ($) {
  return is_integer($_[0]) || (is_double($_[0]) && defined $_[0]->value);
}

sub character { Rstats::Element::Character->new(value => shift) }
sub complex {
  my ($re_value, $im_value) = @_;
  
  my $re = double($re_value);
  my $im = double($im_value);
  my $z = complex_double($re, $im);
  
  return $z;
}
sub complex_double {
  my ($re, $im) = @_;
  
  my $z = Rstats::Element::Complex->new(re => $re, im => $im);
}
sub double { Rstats::Element::Double->new(value => shift, flag => shift || 'normal') }
sub integer { Rstats::Element::Integer->new(value => int(shift)) }
sub logical { Rstats::Element::Logical->new(value => shift) }

sub atanh {
  my $e1 = shift;
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
    if (equal($e1, complex(1, 0))) {
      $e2 = complex_double(Inf, NaN);
      carp("In atanh() : NaNs produced");
    }
    elsif (equal($e1, complex(-1, 0))) {
      $e2 = complex_double(negativeInf, NaN);
      carp("In atanh() : NaNs produced");
    }
    else {
      $e2 = multiply(
        complex(0.5, 0),
        Rstats::ElementFunction::log(
          divide(
            add(complex(1, 0), $e1),
            subtract(complex(1, 0), $e1)
          )
        )
      );
    }
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    $e1 = Rstats::ElementFunction::as_double($e1);
    return $e1 if is_nan($e1);
    
    if (is_infinite($e1)) {
        $e2 = NaN;
        carp "In acosh() : NaNs produced";
    }
    else {
      if (equal($e1, double(1))) {
        $e2 = Inf;
      }
      elsif (equal($e1, double(-1))) {
        $e2 = negativeInf;
      }
      elsif (less_than(Rstats::ElementFunction::abs($e1), double(1))) {
        $e2 = divide(
          Rstats::ElementFunction::log(
            divide(
              add(double(1), $e1),
              subtract(double(1), $e1)
            )
          ),
          double(2)
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
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
    my $e1_re = Re($e1);
    my $e1_im = Im($e1);

    my $e2_t = add(
      Rstats::ElementFunction::sqrt(
        subtract(
          multiply($e1, $e1),
          complex(1, 0)
        ),
      ),
      $e1
    );
    my $e2_u = Rstats::ElementFunction::log($e2_t);
    my $e2_re = Re($e2_u);
    my $e2_im = Im($e2_u);
    
    if (less_than($e1_re, double(0)) && equal($e1_im, double(0))) {
      $e2 = complex_double($e2_re, negation($e2_im));
    }
    else {
      $e2 = complex_double($e2_re, $e2_im);
    }
    
    if (less_than($e1_re, double(0))) {
      $e2 = negation($e2);
    }
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    $e1 = Rstats::ElementFunction::as_double($e1);
    return $e1 if is_nan($e1);
    
    if (is_infinite($e1)) {
        $e2 = NaN;
        carp "In acosh() : NaNs produced";
    }
    else {
      if (more_than_or_equal($e1, double(1))) {
        $e2 = Rstats::ElementFunction::log(
          add(
            $e1,
            Rstats::ElementFunction::sqrt(
              subtract(
                multiply($e1, $e1),
                double(1)
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
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
  
    my $e2_t = add(
      Rstats::ElementFunction::sqrt(
        add(
          multiply($e1, $e1),
          complex(1, 0)
        )
      ),
      $e1
    );
    
    $e2 = Rstats::ElementFunction::log($e2_t);
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    $e1 = Rstats::ElementFunction::as_double($e1);
    return $e1 if is_nan($e1);
    
    if (is_positive_infinite($e1)) {
      $e2 = Inf;
    }
    elsif (is_negative_infinite($e1)) {
      $e2 = negativeInf;
    }
    else {
      my $e2_t = add(
        $e1,
        Rstats::ElementFunction::sqrt(
          add(
            multiply($e1, $e1),
            double(1)
          )
        )
      );
      
      $e2 = Rstats::ElementFunction::log($e2_t);
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub tanh {
  my $e1 = shift;
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
    if (is_infinite(Im($e1))) {
      $e2 = complex_double(NaN, NaN);
    }
    elsif (is_positive_infinite(Re($e1))) {
      $e2 = complex(1, 0);
    }
    elsif (is_negative_infinite(Re($e1))) {
      $e2 = complex(-1, 0);
    }
    else {
      $e2 = divide(sinh($e1), cosh($e1));
    }
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    $e1 = Rstats::ElementFunction::as_double($e1);
    
    return $e1 if is_nan($e1);
    
    if (is_positive_infinite($e1)) {
      $e2 = double(1);
    }
    elsif (is_negative_infinite($e1)) {
      $e2 = double(-1);
    }
    else {
      $e2 = divide(sinh($e1), cosh($e1));
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub cosh {
  my $e1 = shift;
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
    my $e1_x = Re($e1);
    my $e1_y = Im($e1);
    
    my $e2_cy = Rstats::ElementFunction::cos($e1_y);
    my $e2_sy = Rstats::ElementFunction::sin($e1_y);
    my $e2_ex = Rstats::ElementFunction::exp($e1_x);
    
    my $e2_ex_1 = not_equal($e2_ex, double(0)) ? divide(double(1), $e2_ex) : Inf;

    my $e2_x = divide(
      multiply(
        $e2_cy,
        add($e2_ex, $e2_ex_1)
      ),
      double(2)
    );
    my $e2_y = divide(
      multiply(
        $e2_sy,
        subtract($e2_ex, $e2_ex_1)
      ),
      double(2)
    );
    
    $e2 = complex_double($e2_x, $e2_y);
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    $e1 = Rstats::ElementFunction::as_double($e1);
    return $e1 if is_nan($e1);
    
    my $e2_ex = Rstats::ElementFunction::exp($e1);
    
    if (not_equal($e2_ex, double(0))) {
      if (is_positive_infinite($e2_ex)) {
        $e2 = Inf;
      }
      else {
        $e2 = divide(
          add(
            $e2_ex,
            divide(double(1), $e2_ex)
          ),
          double(2)
        )
      }
    }
    else {
      $e2 = Inf;
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub sinh {
  my $e1 = shift;
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
    my $e1_x = Re($e1);
    my $e1_y = Im($e1);
    
    my $e2_cy = Rstats::ElementFunction::cos($e1_y);
    my $e2_sy = Rstats::ElementFunction::sin($e1_y);
    my $e2_ex = Rstats::ElementFunction::exp($e1_x);
    
    my $e2_ex_1 = not_equal($e2_ex, double(0)) ? divide(double(1), $e2_ex) : Inf;

    my $e2_x = divide(
      multiply(
        $e2_cy,
        subtract($e2_ex, $e2_ex_1)
      ),
      double(2)
    );
    my $e2_y = divide(
      multiply(
        $e2_sy,
        add($e2_ex, $e2_ex_1)
      ),
      double(2)
    );
    
    $e2 = complex_double($e2_x, $e2_y);
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    $e1 = Rstats::ElementFunction::as_double($e1);
    return $e1 if is_nan($e1);
    
    return double(0) if equal($e1, double(0));
    my $e2_ex = Rstats::ElementFunction::exp($e1);
    
    if (not_equal($e2_ex, double(0))) {
      if (is_positive_infinite($e2_ex)) {
        $e2 = Inf;
      }
      else {
        $e2 = divide(
          subtract(
            $e2_ex,
            divide(double(1), $e2_ex)
          ),
          double(2)
        )
      }
    }
    else {
      $e2 = negativeInf;
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub atan {
  my $e1 = shift;
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
    
    if (equal($e1, complex(0, 0))) {
      $e2 = complex(0, 0);
    }
    elsif (equal($e1, complex(0, 1))) {
      $e2 = complex(0, Inf);
    }
    elsif (equal($e1, complex(0, -1))) {
      $e2 = complex(0, negativeInf);
    }
    else {
      my $e2_i = complex(0, 1);
      my $e2_log = Rstats::ElementFunction::log(
        divide(
          add($e2_i, $e1),
          subtract($e2_i, $e1)
        )
      );
      
      $e2 = multiply(
        divide($e2_i, complex(2, 0)),
        $e2_log
      );
    }
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    $e2 = Rstats::ElementFunction::atan2(as_double($e1), double(1));
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}


sub atan2 {
  my ($e1, $e2) = @_;
  
  croak "argument x is missing" unless defined $e2;
  return Rstats::ElementFunction::NA if is_na($e1) || is_na($e2);
  croak "two element should be same type" unless typeof($e1) eq typeof($e2);
  
  my $e3;
  if (is_complex($e1)) {
    
    my $e3_s = add(multiply($e1, $e1), multiply($e2, $e2));
    if (equal($e3_s, complex(0, 0))) {
      $e3 = complex(0, 0);
    }
    else {
      my $e3_i = complex(0, 1);
      my $e3_r = add($e2, multiply($e1, $e3_i));
      $e3 = multiply(
        negation($e3_i),
        Rstats::ElementFunction::log(
          divide(
            $e3_r,
            Rstats::ElementFunction::sqrt($e3_s)
          )
        )
      );
    }
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    my $value1;
    my $value2;
    
    if (is_nan($e1) || is_nan($e2)) {
      $e3 = Rstats::ElementFunction::NaN;
    }
    elsif (is_positive_infinite($e1) && is_positive_infinite($e2)) {
      $e3 = double(0.785398163397448);
    }
    elsif (is_positive_infinite($e1) && is_negative_infinite($e2)) {
      $e3 = double(2.35619449019234);
    }
    elsif (is_negative_infinite($e1) && is_positive_infinite($e2)) {
      $e3 = double(-0.785398163397448);
    }
    elsif (is_negative_infinite($e1) && is_negative_infinite($e2)) {
      $e3 = double(-2.35619449019234);
    }
    elsif (is_positive_infinite($e1)) {
      $e3 = double(1.5707963267949);
    }
    elsif (is_positive_infinite($e2)) {
      $e3 = double(0)
    }
    elsif (is_negative_infinite($e1)) {
      $e3 = double(-1.5707963267949);
    }
    elsif (is_negative_infinite($e2)) {
      my $value1 = value($e1);
      if ($value1 >= 0) {
        $e3 = double(3.14159265358979);
      }
      else {
        $e3 = double(-3.14159265358979);
      }
    }
    else {
      my $value1 = value($e1);
      my $value2 = value($e2);
      $e3 = double(CORE::atan2($value1, $value2));
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e3;
}

sub log2 {
  my $e1 = shift;
  
  my $e2 = divide(
    Rstats::ElementFunction::log($e1),
    is_complex($e1) ? Rstats::ElementFunction::log(complex(2, 0)) : Rstats::ElementFunction::log(double(2))
  );
  
  return $e2;
}

sub log10 {
  my $e1 = shift;
  
  my $e2 = divide(
    Rstats::ElementFunction::log($e1),
    is_complex($e1) ? Rstats::ElementFunction::log(complex(10, 0)) : Rstats::ElementFunction::log(double(10))
  );
  
  return $e2;
}

sub log {
  my $e1 = shift;
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
    
    my $e1_r = Mod($e1);
    my $e1_t = Arg($e1);
    
    if (equal($e1_r, double(0))) {
      $e2 = negativeInf;
    }
    else {
      if (more_than($e1_t, pi)) {
        $e1_t = subtract(
          $e1_t,
          multiply(
            pi,
            pi
          )
        )
      }
      elsif (less_than_or_equal($e1_t, negation(pi))) {
        $e1_t = add(
          $e1_t,
          multiply(
            pi,
            pi
          )
        )
      }
      
      $e2 = complex_double(Rstats::ElementFunction::log($e1_r), $e1_t);
    }
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    my $value = value($e1);
    
    if (is_infinite($e1)) {
      carp "In cos : NaNs produced";
      $e2 = NaN;
    }
    elsif (is_nan($e1)) {
      $e2 = $e1;
    }
    else {
      if ($value < 0) {
        carp "In log : NaNs produced";
        $e2 = NaN
      }
      elsif ($value == 0) {
        $e2 = negativeInf;
      }
      else {
        $e2 = double(log($value));
      }
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub Mod { Rstats::ElementFunction::abs(@_) }

sub Arg {
  my $e1 = shift;
  
  if (is_complex($e1)) {
    my $e1_re = Re($e1);
    my $e1_im = Im($e1);
    my $re = value($e1_re);
    my $im = value($e1_im);
    
    my $e2;
    if ($re == 0 && $im == 0) {
      $e2 = double(0);
    }
    else {
      $e2 = double(CORE::atan2($im, $re));
    }
    
    return $e2;
  }
  else {
    croak "Not implemented";
  }
}

sub hash {
  my $e1 = shift;
  
  my $hash = typeof($e1) . '-' . to_string($e1);
  
  return $hash;
}

sub tan {
  my $e1 = shift;
  
  my $e2 = divide(Rstats::ElementFunction::sin($e1), Rstats::ElementFunction::cos($e1));
  
  return $e2;
}

sub cos {
  my $e1 = shift;
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
    
    my $e1_re = Re($e1);
    my $e1_im = Im($e1);
    
    my $e2_eim = Rstats::ElementFunction::exp($e1_im);
    my $e2_sre = Rstats::ElementFunction::sin($e1_re);
    my $e2_cre = Rstats::ElementFunction::cos($e1_re);
    
    my $e2_eim_1 = divide(double(1), $e2_eim);
    
    my $e2_re = divide(
      multiply(
        $e2_cre,
        add(
          $e2_eim,
          $e2_eim_1
        )
      ),
      double(2)
    );
    
    my $e2_im = divide(
      multiply(
        $e2_sre,
        subtract(
          $e2_eim_1,
          $e2_eim
        )
      ),
      double(2)
    );
    
    $e2 = complex_double($e2_re, $e2_im);
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    my $value = value($e1);
    
    if (is_infinite($e1)) {
      carp "In cos : NaNs produced";
      $e2 = NaN;
    }
    elsif (is_nan($e1)) {
      $e2 = $e1;
    }
    else {
      $e2 = double(cos($value));
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub exp {
  my $e1 = shift;
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
    
    my $e1_re = Re($e1);
    my $e1_im = Im($e1);
    
    my $e2_mod = Rstats::ElementFunction::exp($e1_re);
    my $e2_arg = $e1_im;

    my $e2_re = Rstats::ElementFunction::multiply(
      $e2_mod,
      Rstats::ElementFunction::cos($e2_arg)
    );
    my $e2_im = Rstats::ElementFunction::multiply(
      $e2_mod,
      Rstats::ElementFunction::sin($e2_arg)
    );
    
    $e2 = complex_double($e2_re, $e2_im);
  }
  elsif (is_double($e1) || is_integer($e1) || is_logical($e1)) {
    $e1 = as_double($e1);
    
    if (is_positive_infinite($e1)) {
      $e2 = Inf;
    }
    elsif (is_negative_infinite($e1)) {
      $e2 = double(0);
    }
    elsif (is_nan($e1)) {
      $e2 = $e1;
    }
    else {
      my $value = value($e1);
      $e2 = double(exp($value));
    }
  }
  else {
    croak "Not implemented";
  }
  
  return $e2;
}

sub expm1 {
  my $e1 = shift;
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
    croak 'Error in expm1 : unimplemented complex function';
  }
  elsif (is_double($e1)) {
    if (less_than($e1, double(1e-5)) && more_than($e1, negativeInf)) {
      $e2 = add(
        $e1,
        multiply(
          double(0.5),
          multiply(
            $e1,
            $e1
          )
        )
      );
    }
    else {
      $e2 = Rstats::ElementFunction::subtract(Rstats::ElementFunction::exp($e1), double(1));
    }
  }
  elsif (is_integer($e1) || is_logical($e1)) {
    $e2 = Rstats::ElementFunction::subtract(Rstats::ElementFunction::exp($e1), double(1));
  }
  else {
    croak 'Not implemented';
  }
}

sub acos {
  my $e1 = shift;

  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {

    my $e1_re = Re($e1);
    my $e1_im = Im($e1);
    
    if (equal($e1_re, double(1)) && equal($e1_im, double(0))) {
      $e2 = complex(0, 0);
    }
    else {
      my $e2_t1 = Rstats::ElementFunction::sqrt(
        add(
          multiply(
            add($e1_re, double(1)),
            add($e1_re, double(1))
          ),
          multiply($e1_im, $e1_im)
        )
      );
      my $e2_t2 = Rstats::ElementFunction::sqrt(
        add(
          multiply(
            subtract($e1_re, double(1)),
            subtract($e1_re, double(1))
          ),
          multiply($e1_im, $e1_im)
        )
      );
      
      my $e2_alpha = divide(
        add($e2_t1,  $e2_t2),
        double(2)
      );
      
      my $e2_beta  = divide(
        subtract($e2_t1, $e2_t2),
        double(2)
      );
      
      if (less_than($e2_alpha, double(1))) {
        $e2_alpha = double(1);
      }
      
      if (more_than($e2_beta,double(1))) {
        $e2_beta =  double(1);
      }
      elsif (less_than($e2_beta, double(-1))) {
        $e2_beta = double(-1);
      }
      
      my $e2_u =  Rstats::ElementFunction::atan2(
        Rstats::ElementFunction::sqrt(
          subtract(
            double(1),
            multiply($e2_beta, $e2_beta)
          )
        ),
        $e2_beta
      );
      
      my $e2_v = Rstats::ElementFunction::log(
        add(
          $e2_alpha,
          Rstats::ElementFunction::sqrt(
            subtract(
              multiply($e2_alpha, $e2_alpha),
              double(1)
            )
          )
        )
      );
      
      if (more_than($e1_im, double(0)) || (equal($e1_im, double(0)) && less_than($e1_re, double(-1)))) {
        $e2_v = negation($e2_v);
      }
      
      $e2 = complex_double($e2_u, $e2_v);
    }
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    if (is_infinite($e1)) {
      carp "In sin : NaNs produced";
      $e2 = NaN;
    }
    elsif (is_nan($e1)) {
      $e2 = $e1;
    }
    else {
      $e1 = as_double($e1);
      if (less_than_or_equal(Rstats::ElementFunction::abs($e1), double(1))) {
        $e2 = Rstats::ElementFunction::atan2(
          Rstats::ElementFunction::sqrt(
            subtract(
              double(1),
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

  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {

    my $e1_re = Re($e1);
    my $e1_im = Im($e1);
    
    if (equal($e1_re, double(0)) && equal($e1_im, double(0))) {
      $e2 = complex(0, 0);
    }
    else {
      my $e2_t1 = Rstats::ElementFunction::sqrt(
        add(
          multiply(
            add($e1_re, double(1)),
            add($e1_re, double(1))
          ),
          multiply($e1_im, $e1_im)
        )
      );
      my $e2_t2 = Rstats::ElementFunction::sqrt(
        add(
          multiply(
            subtract($e1_re, double(1)),
            subtract($e1_re, double(1))
          ),
          multiply($e1_im, $e1_im)
        )
      );
      
      my $e2_alpha = divide(
        add($e2_t1,  $e2_t2),
        double(2)
      );
      
      my $e2_beta  = divide(
        subtract($e2_t1, $e2_t2),
        double(2)
      );
      
      if (less_than($e2_alpha, double(1))) {
        $e2_alpha = double(1);
      }
      
      if (more_than($e2_beta,double(1))) {
        $e2_beta =  double(1);
      }
      elsif (less_than($e2_beta, double(-1))) {
        $e2_beta = double(-1);
      }
      
      my $e2_u =  Rstats::ElementFunction::atan2(
        $e2_beta,
        Rstats::ElementFunction::sqrt(
          subtract(
            double(1),
            multiply($e2_beta, $e2_beta)
          )
        )
      );
      
      my $e2_v = negation(
        Rstats::ElementFunction::log(
          add(
            $e2_alpha,
            Rstats::ElementFunction::sqrt(
              subtract(
                multiply($e2_alpha, $e2_alpha),
                double(1)
              )
            )
          )
        )
      );
      
      if (more_than($e1_im, double(0)) || (equal($e1_im, double(0)) && less_than($e1_re, double(-1)))) {
        $e2_v = negation($e2_v);
      }
      
      $e2 = complex_double($e2_u, $e2_v);
    }
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    if (is_infinite($e1)) {
      carp "In sin : NaNs produced";
      $e2 = NaN;
    }
    elsif (is_nan($e1)) {
      $e2 = $e1;
    }
    else {
      $e1 = as_double($e1);
      if (less_than_or_equal(Rstats::ElementFunction::abs($e1), double(1))) {
        $e2 = Rstats::ElementFunction::atan2(
          $e1,
          Rstats::ElementFunction::sqrt(
            subtract(
              double(1),
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

sub sin {
  my $e1 = shift;
  
  return $e1 if is_na($e1);
  
  my $e2;
  if (is_complex($e1)) {
    
    my $e1_re = Re($e1);
    my $e1_im = Im($e1);
    
    my $e2_eim = Rstats::ElementFunction::exp($e1_im);
    my $e2_sre = Rstats::ElementFunction::sin($e1_re);
    my $e2_cre = Rstats::ElementFunction::cos($e1_re);
    
    my $e2_eim_1 = divide(double(1), $e2_eim);
    
    my $e2_re = divide(
      multiply(
        $e2_sre,
        add(
          $e2_eim,
          $e2_eim_1
        )
      ),
      double(2)
    );
    
    my $e2_im = divide(
      multiply(
        $e2_cre,
        subtract(
          $e2_eim,
          $e2_eim_1
        )
      ),
      double(2)
    );
    
    $e2 = complex_double($e2_re, $e2_im);
  }
  elsif (is_numeric($e1) || is_logical($e1)) {
    my $value = value($e1);
    
    if (is_infinite($e1)) {
      carp "In sin : NaNs produced";
      $e2 = NaN;
    }
    elsif (is_nan($e1)) {
      $e2 = $e1;
    }
    else {
      $e2 = double(sin($value));
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
    return complex($value, 0);
  }
  elsif ($type eq 'double') {
    return double($value);
  }
  elsif ($type eq 'integer') {
    return integer($value);
  }
  elsif ($type eq 'logical') {
    return logical($value ? Rstats::ElementFunction::TRUE : Rstats::ElementFunction::FALSE);
  }
  else {
    croak 'Invalid type';
  }
}

sub looks_like_number {
  my $value = shift;
  
  return if !defined $value || !CORE::length $value;
  $value =~ s/^ +//;
  $value =~ s/ +$//;
  
  if (Scalar::Util::looks_like_number $value) {
    return $value + 0;
  }
  else {
    return;
  }
}

sub looks_like_complex {
  my $value = shift;
  
  return if !defined $value || !CORE::length $value;
  $value =~ s/^ +//;
  $value =~ s/ +$//;
  
  my $re;
  my $im;
  
  if ($value =~ /^([\+\-]?[^\+\-]+)i$/) {
    $re = 0;
    $im = $1;
  }
  elsif($value =~ /^([\+\-]?[^\+\-]+)(?:([\+\-][^\+\-i]+)i)?$/) {
    $re = $1;
    $im = $2;
    $im = 0 unless defined $im;
  }
  else {
    return;
  }
  
  if (defined Rstats::ElementFunction::looks_like_number($re) && defined Rstats::ElementFunction::looks_like_number($im)) {
    return {re => $re + 0, im => $im + 0};
  }
  else {
    return;
  }
}

sub element {
  my $value = shift;
  
  return ref $value ? $value
    : is_perl_number($value) ? double($value)
    : character($value);

}

sub value {
  my $element = shift;
  
  if (is_character($element)
    || is_integer($element)
    || (is_double($element) && !is_nan($element) && !is_infinite($element))
  ) {
    return $element->value;
  }
  elsif (is_complex($element)) {
    return {
      re => value($element->re),
      im => value($element->im)
    };
  }
  else {
    return $element;
  }
}

sub is_perl_number {
  my ($value) = @_;
  
  return unless defined $value;
  
  return B::svref_2object(\$value)->FLAGS & (B::SVp_IOK | B::SVp_NOK) 
        && 0 + $value eq $value
        && $value * 0 == 0
}

sub to_string {
  my $element = shift;
  
  if (is_na($element)) {
    return 'NA';
  }
  elsif (is_character($element)) {
    return $element->value . "";
  }
  elsif (is_complex($element)) {
    my $re = to_string($element->re);
    my $im = to_string($element->im);
    
    my $str = "$re";
    $str .= '+' if $im >= 0;
    $str .= $im . 'i';
  }
  elsif (is_double($element)) {
    
    my $flag = $element->flag;
    
    if (defined $element->value) {
      return $element->value . "";
    }
    elsif ($flag eq 'nan') {
      return 'NaN';
    }
    elsif ($flag eq 'inf') {
      return 'Inf';
    }
    elsif ($flag eq '-inf') {
      return '-Inf';
    }
  }
  elsif (is_integer($element)) {
    return $element->value . "";
  }
  elsif (is_logical($element)) {
    return $element->value ? 'TRUE' : 'FALSE'
  }
  else {
    croak "Invalid type";
  }
}

sub negation {
  my $e1 = shift;
  
  if (is_na($e1)) {
    return NA;
  }
  elsif (is_character($e1)) {
    croak 'argument is not interpretable as logical'
  }
  elsif (is_complex($e1)) {
    return complex_double(negation($e1->re), negation($e1->im));
  }
  elsif (is_double($e1)) {
    
    my $flag = $e1->flag;
    if (defined $e1->value) {
      return double(-$e1->value);
    }
    elsif ($flag eq 'nan') {
      return NaN;
    }
    elsif ($flag eq 'inf') {
      return negativeInf;
    }
    elsif ($flag eq '-inf') {
      return Inf;
    }
  }
  elsif (is_integer($e1) || is_logical($e1)) {
    return integer(-$e1->value);
  }
  else {
    croak "Invalid type";
  }  
}

sub bool {
  my $e1 = shift;
  
  if (is_na($e1)) {
    croak "Error in bool context (a) { : missing value where TRUE/FALSE needed"
  }
  elsif (is_character($e1) || is_complex($e1)) {
    croak 'Error in -a : invalid argument to unary operator ';
  }
  elsif (is_double($e1)) {

    if (defined $e1->value) {
      return $e1->value;
    }
    else {
      if (is_infinite($e1)) {
        1;
      }
      # NaN
      else {
        croak 'argument is not interpretable as logical'
      }
    }
  }
  elsif (is_integer($e1) || is_logical($e1)) {
    return $e1->value;
  }
  else {
    croak "Invalid type";
  }  
}

sub add {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    croak "Error in a + b : non-numeric argument to binary operator";
  }
  elsif (is_complex($e1)) {
    my $re = add($e1->{re}, $e2->{re});
    my $im = add($e1->{im}, $e2->{im});
    
    return complex_double($re, $im);
  }
  elsif (is_double($e1)) {
    return NaN if is_nan($e1) || is_nan($e2);
    if (defined $e1->value) {
      if (defined $e2->value) {
        my $value = $e1->value + $e2->value;
        if ($value == $perl_inf_result) {
          return Inf;
        }
        elsif ($value == $perl_negative_inf_result) {
          return negativeInf;
        }
        else {
          return double($value)
        }
      }
      elsif (is_positive_infinite($e2)) {
        return Inf;
      }
      elsif (is_negative_infinite($e2)) {
        return negativeInf;
      }
    }
    elsif (is_positive_infinite($e1)) {
      if (defined $e2->value) {
        return Inf;
      }
      elsif (is_positive_infinite($e2)) {
        return Inf;
      }
      elsif (is_negative_infinite($e2)) {
        return NaN;
      }
    }
    elsif (is_negative_infinite($e1)) {
      if (defined $e2->value) {
        return negativeInf;
      }
      elsif (is_positive_infinite($e2)) {
        return NaN;
      }
      elsif (is_negative_infinite($e2)) {
        return negativeInf;
      }
    }
  }
  elsif (is_integer($e1)) {
    return integer($e1->value + $e2->value);
  }
  elsif (is_logical($e1)) {
    return integer($e1->value + $e2->value);
  }
  else {
    croak "Invalid type";
  }
}

sub subtract {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    croak "Error in a + b : non-numeric argument to binary operator";
  }
  elsif (is_complex($e1)) {
    my $re = subtract($e1->{re}, $e2->{re});
    my $im = subtract($e1->{im}, $e2->{im});
    
    return complex_double($re, $im);
  }
  elsif (is_double($e1)) {
    return NaN if is_nan($e1) || is_nan($e2);
    if (defined $e1->value) {
      if (defined $e2->value) {
        my $value = $e1->value - $e2->value;
        if ($value == $perl_inf_result) {
          return Inf;
        }
        elsif ($value == $perl_negative_inf_result) {
          return negativeInf;
        }
        else {
          return double($value)
        }
      }
      elsif (is_positive_infinite($e2)) {
        return negativeInf;
      }
      elsif (is_negative_infinite($e2)) {
        return Inf;
      }
    }
    elsif (is_positive_infinite($e1)) {
      if (defined $e2->value) {
        return Inf;
      }
      elsif (is_positive_infinite($e2)) {
        return NaN;
      }
      elsif (is_negative_infinite($e2)) {
        return Inf;
      }
    }
    elsif (is_negative_infinite($e1)) {
      if (defined $e2->value) {
        return negativeInf;
      }
      elsif (is_positive_infinite($e2)) {
        return negativeInf;
      }
      elsif (is_negative_infinite($e2)) {
        return NaN;
      }
    }
  }
  elsif (is_integer($e1)) {
    return integer($e1->value + $e2->value);
  }
  elsif (is_logical($e1)) {
    return integer($e1->value + $e2->value);
  }
  else {
    croak "Invalid type";
  }
}

sub multiply {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    croak "Error in a + b : non-numeric argument to binary operator";
  }
  elsif (is_complex($e1)) {
    my $re = subtract(multiply($e1->re, $e2->re), multiply($e1->im, $e2->im));
    my $im = add(multiply($e1->re, $e2->im), multiply($e1->im, $e2->re));
    
    return complex_double($re, $im);
  }
  elsif (is_double($e1)) {
    return NaN if is_nan($e1) || is_nan($e2);
    if (defined $e1->value) {
      if (defined $e2->value) {
        my $value = value($e1) * value($e2);
        if ($value == $perl_inf_result) {
          return Inf;
        }
        elsif ($value == $perl_negative_inf_result) {
          return negativeInf;
        }
        else {
          return double($value)
        }
      }
      elsif (is_positive_infinite($e2)) {
        if ($e1->value == 0) {
          return NaN;
        }
        elsif ($e1->value > 0) {
          return Inf;
        }
        elsif ($e1->value < 0) {
          return negativeInf;
        }
      }
      elsif (is_negative_infinite($e2)) {
        if ($e1->value == 0) {
          return NaN;
        }
        elsif ($e1->value > 0) {
          return negativeInf;
        }
        elsif ($e1->value < 0) {
          return Inf;
        }
      }
    }
    elsif (is_positive_infinite($e1)) {
      if (defined $e2->value) {
        if ($e2->value == 0) {
          return NaN;
        }
        elsif ($e2->value > 0) {
          return Inf;
        }
        elsif ($e2->value < 0) {
          return negativeInf;
        }
      }
      elsif (is_positive_infinite($e2)) {
        return Inf;
      }
      elsif (is_negative_infinite($e2)) {
        return negativeInf;
      }
    }
    elsif (is_negative_infinite($e1)) {
      if (defined $e2->value) {
        if ($e2->value == 0) {
          return NaN;
        }
        elsif ($e2->value > 0) {
          return negativeInf;
        }
        elsif ($e2->value < 0) {
          return Inf;
        }
      }
      elsif (is_positive_infinite($e2)) {
        return negativeInf;
      }
      elsif (is_negative_infinite($e2)) {
        return Inf;
      }
    }
  }
  elsif (is_integer($e1)) {
    return integer($e1->value * $e2->value);
  }
  elsif (is_logical($e1)) {
    return integer($e1->value * $e2->value);
  }
  else {
    croak "Invalid type";
  }
}

sub divide {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    croak "Error in a + b : non-numeric argument to binary operator";
  }
  elsif (is_complex($e1)) {
    my $v3 = multiply($e1, Conj($e2));
    my $abs2 = double(value($e2->re) ** 2 + value($e2->im) ** 2);
    my $re = divide($v3->re, $abs2);
    my $im = divide($v3->im, $abs2);
    
    return complex_double($re, $im);
  }
  elsif (is_double($e1)) {
    return NaN if is_nan($e1) || is_nan($e2);
    if (defined $e1->value) {
      if ($e1->value == 0) {
        if (defined $e2->value) {
          if ($e2->value == 0) {
            return NaN;
          }
          else {
            return double(0)
          }
        }
        elsif (is_infinite($e2)) {
          return double(0);
        }
      }
      elsif ($e1->value > 0) {
        if (defined $e2->value) {
          if ($e2->value == 0) {
            return Inf;
          }
          else {
            my $value = $e1->value / $e2->value;
            if ($value == $perl_inf_result) {
              return Inf;
            }
            elsif ($value == $perl_negative_inf_result) {
              return negativeInf;
            }
            else {
              return double($value)
            }
          }
        }
        elsif (is_infinite($e2)) {
          return double(0);
        }
      }
      elsif ($e1->value < 0) {
        if (defined $e2->value) {
          if ($e2->value == 0) {
            return negativeInf;
          }
          else {
            return double($e1->value / $e2->value);
          }
        }
        elsif (is_infinite($e2)) {
          return double(0);
        }
      }
    }
    elsif (is_positive_infinite($e1)) {
      if (defined $e2->value) {
        if ($e2->value >= 0) {
          return Inf;
        }
        elsif ($e2->value < 0) {
          return negativeInf;
        }
      }
      elsif (is_infinite($e2)) {
        return NaN;
      }
    }
    elsif (is_negative_infinite($e1)) {
      if (defined $e2->value) {
        if ($e2->value >= 0) {
          return negativeInf;
        }
        elsif ($e2->value < 0) {
          return Inf;
        }
      }
      elsif (is_infinite($e2)) {
        return NaN;
      }
    }
  }
  elsif (is_integer($e1)) {
    if ($e1->value == 0) {
      if ($e2->value == 0) {
        return NaN;
      }
      else {
        return double(0);
      }
    }
    elsif ($e1->value > 0) {
      if ($e2->value == 0) {
        return Inf;
      }
      else  {
        return double($e1->value / $e2->value);
      }
    }
    elsif ($e1->value < 0) {
      if ($e2->value == 0) {
        return negativeInf;
      }
      else {
        return double($e1->value / $e2->value);
      }
    }
  }
  elsif (is_logical($e1)) {
    if ($e1->value == 0) {
      if ($e2->value == 0) {
        return NaN;
      }
      elsif ($e2->value == 1) {
        return double(0);
      }
    }
    elsif ($e1->value == 1) {
      if ($e2->value == 0) {
        return Inf;
      }
      elsif ($e2->value == 1)  {
        return double(1);
      }
    }
  }
  else {
    croak "Invalid type";
  }
}

sub raise {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    croak "Error in a + b : non-numeric argument to binary operator";
  }
  elsif (is_complex($e1)) {
    my $e1_c = Math::Complex->make(Rstats::ElementFunction::value($e1->re), Rstats::ElementFunction::value($e1->im));
    my $e2_c = Math::Complex->make(Rstats::ElementFunction::value($e2->re), Rstats::ElementFunction::value($e2->im));
    
    my $v3_c;
    if ($e2->re->value == 1/2 && $e2->im->value == 0) {
      $v3_c = Math::Complex::sqrt($e1_c);
    }
    else {
      $v3_c = $e1_c ** $e2_c;
    }
    my $re = Math::Complex::Re($v3_c);
    my $im = Math::Complex::Im($v3_c);
    
    return complex($re, $im);
  }
  elsif (is_double($e1)) {
    return NaN if is_nan($e1) || is_nan($e2);
    if (defined $e1->value) {
      if ($e1->value == 0) {
        if (defined $e2->value) {
          if ($e2->value == 0) {
            return double(1);
          }
          elsif ($e2->value > 0) {
            return double(0);
          }
          elsif ($e2->value < 0) {
            return Inf;
          }
        }
        elsif (is_positive_infinite($e2)) {
          return double(0);
        }
        elsif (is_negative_infinite($e2)) {
          return Inf
        }
      }
      elsif ($e1->value > 0) {
        if (defined $e2->value) {
          if ($e2->value == 0) {
            return double(1);
          }
          else {
            my $value = $e1->value ** $e2->value;
            if ($value == $perl_inf_result) {
              return Inf;
            }
            elsif ($value == $perl_negative_inf_result) {
              return negativeInf;
            }
            else {
              return double($value)
            }
          }
        }
        elsif (is_positive_infinite($e2)) {
          if ($e1->value < 1) {
            return double(0);
          }
          elsif ($e1->value == 1) {
            return double(1);
          }
          elsif ($e1->value > 1) {
            return Inf;
          }
        }
        elsif (is_negative_infinite($e2)) {
          if ($e1->value < 1) {
            return double(0);
          }
          elsif ($e1->value == 1) {
            return double(1);
          }
          elsif ($e1->value > 1) {
            return double(0);
          }
        }
      }
      elsif ($e1->value < 0) {
        if (defined $e2->value) {
          if ($e2->value == 0) {
            return double(-1);
          }
          else {
            return double($e1->value ** $e2->value);
          }
        }
        elsif (is_positive_infinite($e2)) {
          if ($e1->value > -1) {
            return double(0);
          }
          elsif ($e1->value == -1) {
            return double(-1);
          }
          elsif ($e1->value < -1) {
            return negativeInf;
          }
        }
        elsif (is_negative_infinite($e2)) {
          if ($e1->value > -1) {
            return Inf;
          }
          elsif ($e1->value == -1) {
            return double(-1);
          }
          elsif ($e1->value < -1) {
            return double(0);
          }
        }
      }
    }
    elsif (is_positive_infinite($e1)) {
      if (defined $e2->value) {
        if ($e2->value == 0) {
          return double(1);
        }
        elsif ($e2->value > 0) {
          return Inf;
        }
        elsif ($e2->value < 0) {
          return double(0);
        }
      }
      elsif (is_positive_infinite($e2)) {
        return Inf;
      }
      elsif (is_negative_infinite($e2)) {
        return double(0);
      }
    }
    elsif (is_negative_infinite($e1)) {
      if (defined $e2->value) {
        if ($e2->value == 0) {
          return double(-1);
        }
        elsif ($e2->value > 0) {
          return negativeInf;
        }
        elsif ($e2->value < 0) {
          return double(0);
        }
      }
      elsif (is_positive_infinite($e2)) {
        return negativeInf;
      }
      elsif (is_negative_infinite($e2)) {
        return double(0);
      }
    }
  }
  elsif (is_integer($e1)) {
    if ($e1->value == 0) {
      if ($e2->value == 0) {
        return double(1);
      }
      elsif ($e2->value > 0) {
        return double(0);
      }
      elsif ($e2->value < 0) {
        return Inf;
      }
    }
    elsif ($e1->value > 0) {
      if ($e2->value == 0) {
        return double(1);
      }
      else {
        return double($e1->value ** $e2->value);
      }
    }
    elsif ($e1->value < 0) {
      if ($e2->value == 0) {
        return double(-1);
      }
      else {
        return double($e1->value ** $e2->value);
      }
    }
  }
  elsif (is_logical($e1)) {
    if ($e1->value == 0) {
      if ($e2->value == 0) {
        return double(1);
      }
      elsif ($e2->value == 1) {
        return double(0);
      }
    }
    elsif ($e1->value ==  1) {
      if ($e2->value == 0) {
        return double(1);
      }
      elsif ($e2->value == 1) {
        return double(1);
      }
    }
  }
  else {
    croak "Invalid type";
  }
}

sub remainder {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    croak "Error in a + b : non-numeric argument to binary operator";
  }
  elsif (is_complex($e1)) {
    croak "unimplemented complex operation";
  }
  elsif (is_double($e1)) {
    return NaN if is_nan($e1) || is_nan($e2) || is_infinite($e1) || is_infinite($e2);
    
    if ($e2->value == 0) {
      return NaN;
    }
    else {
      my $v3_value = $e1->value - POSIX::floor($e1->value/$e2->value) * $e2->value;
      return double($v3_value);
    }
  }
  elsif (is_integer($e1)) {
    if ($e2->value == 0) {
      return NaN;
    }
    else {
      return double($e1 % $e2);
    }
  }
  elsif (is_logical($e1)) {
    if ($e2->value == 0) {
      return NaN;
    }
    else {
      return double($e1->value % $e2->value);
    }
  }
  else {
    croak "Invalid type";
  }
}

sub Conj {
  my $value = shift;
  
  if (is_complex($value)) {
    return complex_double($value->re, Rstats::ElementFunction::negation($value->im));
  }
  else {
    croak 'Invalid type';
  }
}

sub Re {
  my $element = shift;
  
  if (is_complex($element)) {
    return $element->{re};
  }
  else {
    'Not implemented';
  }
}

sub Im {
  my $element = shift;
  
  if (is_complex($element)) {
    return $element->{im};
  }
  else {
    'Not implemented';
  }
}

sub abs {
  my $element = shift;
  
  if (is_complex($element)) {
    return raise(add(raise(Re($element), double(2)), raise(Im($element), double(2))), double(1/2));
  }
  elsif (is_double($element) || is_integer($element)) {
    my $type = typeof($element);
    my $zero = Rstats::ElementFunction::create($type);
    if (more_than($element, $zero)) {
      return $element;
    }
    else {
      return negation($element);
    }
  }
  elsif (is_logical($element)) {
    my $zero = Rstats::ElementFunction::create('logical');
    if (more_than($element, $zero)) {
      return logical_to_integer($element);
    }
    else {
      return negation(logical_to_integer($element));
    }
  }
  else {
    croak 'non-numeric argument to mathematical function';
  }
}

sub logical_to_integer {
  my $element = shift;
  
  if (is_logical($element)) {
    return integer($element->value);
  }
  else {
    return $element;
  }
}

sub typeof {
  my $element = shift;
  
  my $type
    = ref $element eq 'Rstats::Element::Character' ? 'character'
    : ref $element eq 'Rstats::Element::Complex' ? 'complex'
    : ref $element eq 'Rstats::Element::Double' ? 'double'
    : ref $element eq 'Rstats::Element::Integer' ? 'integer'
    : ref $element eq 'Rstats::Element::Logical' || ref $element eq 'Rstats::Element::NA' ? 'logical'
    : undef;
  
  return $type;
}

sub is_character { (typeof($_[0]) || '') eq 'character' }
sub is_complex { (typeof($_[0]) || '') eq 'complex' }
sub is_numeric { is_double($_[0]) || is_integer($_[0]) }
sub is_double { (typeof($_[0]) || '') eq 'double' }
sub is_integer { (typeof($_[0]) || '') eq 'integer' }
sub is_logical { (typeof($_[0]) || '') eq 'logical' }

sub as_character {
  my $e1 = shift;
  
  my $e2 = character(to_string($e1));
  
  return $e2;
}

sub as_complex {
  my $e1 = shift;

  if (is_na($e1)) {
    return $e1;
  }
  elsif (is_character($e1)) {
    my $z = looks_like_complex($e1->value);
    if (defined $z) {
      return complex($z->{re}, $z->{im});
    }
    else {
      carp 'NAs introduced by coercion';
      return NA;
    }
  }
  elsif (is_complex($e1)) {
    return $e1;
  }
  elsif (is_double($e1)) {
    if (is_nan($e1)) {
      return NA;
    }
    else {
      return complex_double($e1, double(0));
    }
  }
  elsif (is_integer($e1)) {
    return complex($e1->value, 0);
  }
  elsif (Rstats::ElementFunction::is_logical($e1)) {
    return complex($e1->value ? 1 : 0, 0);
  }
  else {
    croak "unexpected type";
  }
}

sub as_numeric { as_double(@_) }

sub as_double {
  my $e1 = shift;

  if (Rstats::ElementFunction::is_na($e1)) {
    return $e1;
  }
  elsif (is_character($e1)) {
    if (my $num = Rstats::ElementFunction::looks_like_number($e1->value)) {
      return double($num + 0);
    }
    else {
      carp 'NAs introduced by coercion';
      return NA;
    }
  }
  elsif (is_complex($e1)) {
    carp "imaginary parts discarded in coercion";
    return double($e1->re->value);
  }
  elsif (is_double($e1)) {
    return $e1;
  }
  elsif (is_integer($e1)) {
    return double($e1->value);
  }
  elsif (is_logical($e1)) {
    return double($e1->value ? 1 : 0);
  }
  else {
    croak "unexpected type";
  }
}

sub as_integer {
  my $e1 = shift;

  if (is_na($e1)) {
    return $e1;
  }
  elsif (is_character($e1)) {
    if (my $num = Rstats::ElementFunction::looks_like_number($e1->value)) {
      return Rstats::ElementFunction::integer(int $num);
    }
    else {
      carp 'NAs introduced by coercion';
      return NA;
    }
  }
  elsif (is_complex($e1)) {
    carp "imaginary parts discarded in coercion";
    return integer(int($e1->re->value));
  }
  elsif (is_double($e1)) {
    if (is_nan($e1) || is_infinite($e1)) {
      return NA;
    }
    else {
      return Rstats::ElementFunction::integer($e1->value);
    }
  }
  elsif (is_integer($e1)) {
    return $e1; 
  }
  elsif (is_logical($e1)) {
    return integer($e1->value ? 1 : 0);
  }
  else {
    croak "unexpected type";
  }
}

sub as_logical {
  my $e1 = shift;
  
  if (is_na($e1)) {
    return $e1;
  }
  elsif (is_character($e1)) {
    return NA;
  }
  elsif (is_complex($e1)) {
    carp "imaginary parts discarded in coercion";
    my $re = $e1->re->value;
    my $im = $e1->im->value;
    if (defined $re && $re == 0 && defined $im && $im == 0) {
      return FALSE;
    }
    else {
      return TRUE;
    }
  }
  elsif (is_double($e1)) {
    if (is_nan($e1)) {
      return NA;
    }
    elsif (is_infinite($e1)) {
      return TRUE;
    }
    else {
      return $e1->value == 0 ? FALSE : TRUE;
    }
  }
  elsif (is_integer($e1)) {
    return $e1->value == 0 ? FALSE : TRUE;
  }
  elsif (is_logical($e1)) {
    return $e1->value == 0 ? FALSE : TRUE;
  }
  else {
    croak "unexpected type";
  }
}

sub as {
  my ($type, $e1) = @_;
  
  if ($type eq 'character') {
    return as_character($e1);
  }
  elsif ($type eq 'complex') {
    return as_complex($e1);
  }
  elsif ($type eq 'double') {
    return as_double($e1);
  }
  elsif ($type eq 'numeric') {
    return as_numeric($e1);
  }
  elsif ($type eq 'integer') {
    return as_integer($e1);
  }
  elsif ($type eq 'logical') {
    return as_logical($e1);
  }
  else {
    croak "Invalid mode is passed";
  }
}

sub sqrt {
  my $e1 = shift;
  
  my $type = typeof($e1);
  my $e2 = create($type, 1/2);
  
  return raise($e1, $e2);
}

sub more_than {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    return $e1->value gt $e2->value ? TRUE : FALSE;
  }
  elsif (is_complex($e1)) {
    croak "invalid comparison with complex values";
  }
  elsif (is_double($e1)) {
    return NA if is_nan($e1) || is_nan($e2);
    if (defined $e1->value) {
      if (defined $e2->value) {
        return $e1->value > $e2->value ? TRUE : FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return FALSE;
      }
      elsif (is_negative_infinite($e2)) {
        return TRUE;
      }
    }
    elsif (is_positive_infinite($e1)) {
      if (defined $e2->value) {
        return TRUE;
      }
      elsif (is_positive_infinite($e2)) {
        return FALSE;
      }
      elsif (is_negative_infinite($e2)) {
        return TRUE;
      }
    }
    elsif (is_negative_infinite($e1)) {
      if (defined $e2->value) {
        return FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return FALSE;
      }
      elsif (is_negative_infinite($e2)) {
        return FALSE;
      }
    }
  }
  elsif (is_integer($e1)) {
    return $e1->value > $e2->value ? TRUE : FALSE;
  }
  elsif (is_logical($e1)) {
    return $e1->value > $e2->value ? TRUE : FALSE;
  }
  else {
    croak "Invalid type";
  }
}

sub more_than_or_equal {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    return $e1->value ge $e2->value ? TRUE : FALSE;
  }
  elsif (is_complex($e1)) {
    croak "invalid comparison with complex values";
  }
  elsif (is_double($e1)) {
    return NA if is_nan($e1) || is_nan($e2);
    if (defined $e1->value) {
      if (defined $e2->value) {
        return $e1->value >= $e2->value ? TRUE : FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return FALSE;
      }
      elsif (is_negative_infinite($e2)) {
        return TRUE;
      }
    }
    elsif (is_positive_infinite($e1)) {
      if (defined $e2->value) {
        return TRUE;
      }
      elsif (is_positive_infinite($e2)) {
        return TRUE;
      }
      elsif (is_negative_infinite($e2)) {
        return TRUE;
      }
    }
    elsif (is_negative_infinite($e1)) {
      if (defined $e2->value) {
        return FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return FALSE;
      }
      elsif (is_negative_infinite($e2)) {
        return TRUE;
      }
    }
  }
  elsif (is_integer($e1)) {
    return $e1->value >= $e2->value ? TRUE : FALSE;
  }
  elsif (is_logical($e1)) {
    return $e1->value >= $e2->value ? TRUE : FALSE;
  }
  else {
    croak "Invalid type";
  }
}

sub less_than {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    return $e1->value lt $e2->value ? TRUE : FALSE;
  }
  elsif (is_complex($e1)) {
    croak "invalid comparison with complex values";
  }
  elsif (is_double($e1)) {
    return NA if is_nan($e1) || is_nan($e2);
    if (defined $e1->value) {
      if (defined $e2->value) {
        return $e1->value < $e2->value ? TRUE : FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return TRUE;
      }
      elsif (is_negative_infinite($e2)) {
        return FALSE;
      }
    }
    elsif (is_positive_infinite($e1)) {
      if (defined $e2->value) {
        return FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return TRUE;
      }
      elsif (is_negative_infinite($e2)) {
        return FALSE;
      }
    }
    elsif (is_negative_infinite($e1)) {
      if (defined $e2->value) {
        return TRUE;
      }
      elsif (is_positive_infinite($e2)) {
        return TRUE;
      }
      elsif (is_negative_infinite($e2)) {
        return FALSE;
      }
    }
  }
  elsif (is_integer($e1)) {
    return $e1->value < $e2->value ? TRUE : FALSE;
  }
  elsif (is_logical($e1)) {
    return $e1->value < $e2->value ? TRUE : FALSE;
  }
  else {
    croak "Invalid type";
  }
}

sub less_than_or_equal {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    return $e1->value le $e2->value ? TRUE : FALSE;
  }
  elsif (is_complex($e1)) {
    croak "invalid comparison with complex values";
  }
  elsif (is_double($e1)) {
    return NA if is_nan($e1) || is_nan($e2);
    if (defined $e1->value) {
      if (defined $e2->value) {
        return $e1->value <= $e2->value ? TRUE : FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return TRUE;
      }
      elsif (is_negative_infinite($e2)) {
        return FALSE;
      }
    }
    elsif (is_positive_infinite($e1)) {
      if (defined $e2->value) {
        return FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return TRUE;
      }
      elsif (is_negative_infinite($e2)) {
        return FALSE;
      }
    }
    elsif (is_negative_infinite($e1)) {
      if (defined $e2->value) {
        return TRUE;
      }
      elsif (is_positive_infinite($e2)) {
        return TRUE;
      }
      elsif (is_negative_infinite($e2)) {
        return TRUE;
      }
    }
  }
  elsif (is_integer($e1)) {
    return $e1->value <= $e2->value ? TRUE : FALSE;
  }
  elsif (is_logical($e1)) {
    return $e1->value <= $e2->value ? TRUE : FALSE;
  }
  else {
    croak "Invalid type";
  }
}

sub equal {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    return $e1->value eq $e2->value ? TRUE : FALSE;
  }
  elsif (is_complex($e1)) {
    return $e1->re->value == $e2->re->value && $e1->im->value == $e2->im->value ? TRUE : FALSE;
  }
  elsif (is_double($e1)) {
    return NA if is_nan($e1) || is_nan($e2);
    if (defined $e1->value) {
      if (defined $e2->value) {
        return $e1->value == $e2->value ? TRUE : FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return FALSE;
      }
      elsif (is_negative_infinite($e2)) {
        return FALSE;
      }
    }
    elsif (is_positive_infinite($e1)) {
      if (defined $e2->value) {
        return FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return TRUE;
      }
      elsif (is_negative_infinite($e2)) {
        return FALSE;
      }
    }
    elsif (is_negative_infinite($e1)) {
      if (defined $e2->value) {
        return FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return FALSE;
      }
      elsif (is_negative_infinite($e2)) {
        return TRUE;
      }
    }
  }
  elsif (is_integer($e1)) {
    return $e1->value == $e2->value ? TRUE : FALSE;
  }
  elsif (is_logical($e1)) {
    return $e1->value == $e2->value ? TRUE : FALSE;
  }
  else {
    croak "Invalid type";
  }
}

sub not_equal {
  my ($e1, $e2) = @_;
  
  return NA if is_na($e1) || is_na($e2);
  
  if (is_character($e1)) {
    return $e1->value ne $e2->value ? TRUE : FALSE;
  }
  elsif (is_complex($e1)) {
    return !($e1->re->value == $e2->re->value && $e1->im->value == $e2->im->value) ? TRUE : FALSE;
  }
  elsif (is_double($e1)) {
    return NA if is_nan($e1) || is_nan($e2);
    if (defined $e1->value) {
      if (defined $e2->value) {
        return $e1->value != $e2->value ? TRUE : FALSE;
      }
      elsif (is_positive_infinite($e2)) {
        return TRUE;
      }
      elsif (is_negative_infinite($e2)) {
        return TRUE;
      }
    }
    elsif (is_positive_infinite($e1)) {
      if (defined $e2->value) {
        return TRUE;
      }
      elsif (is_positive_infinite($e2)) {
        return FALSE;
      }
      elsif (is_negative_infinite($e2)) {
        return TRUE;
      }
    }
    elsif (is_negative_infinite($e1)) {
      if (defined $e2->value) {
        return TRUE;
      }
      elsif (is_positive_infinite($e2)) {
        return TRUE;
      }
      elsif (is_negative_infinite($e2)) {
        return FALSE;
      }
    }
  }
  elsif (is_integer($e1)) {
    return $e1->value != $e2->value ? TRUE : FALSE;
  }
  elsif (is_logical($e1)) {
    return $e1->value != $e2->value ? TRUE : FALSE;
  }
  else {
    croak "Invalid type";
  }
}

1;