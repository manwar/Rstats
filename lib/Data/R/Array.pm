package Data::R::Array;
use Object::Simple -base;
use Carp 'croak';
use List::Util;

use overload
  bool => sub {1},
  '+' => \&add,
  '-' => \&subtract,
  '*' => \&multiply,
  '/' => \&divide,
  'neg' => \&negation,
  '**' => \&raise,
  '""' => \&to_string,
  fallback => 1;

has 'values';

sub length {
  my $self = shift;
  
  my $length = @{$self->{values}};
  
  return $length;
}

sub is_array {
  my $self = shift;
  
  return (ref $self || '') eq 'Data::R::Array';
}

sub is_vector {
  my $self = shift;
  
  return (ref $self || '') eq 'Data::R::Vector';
}

sub is_matrix {
  my $self = shift;
  
  return (ref $self || '') eq 'Data::R::Matrix';
}

sub dim {
  my ($self, $dim) = @_;
  
  if ($dim) {
    if (ref $dim eq 'ARRAY') {
      $dim = Data::R::Vector->new(values => $dim);
    }
    $self->{dim} = $dim;
  }
  else {
    return $self->{dim};
  }
}

sub as_matrix {
  my $self = shift;
  
  $self->{type} = 'matrix';
}

sub as_array {
  my $self = shift;
  
  $self->{type} = 'array';
}

sub as_vector {
  my $self = shift;
  
  $self->{type} = 'vector';
}

sub new {
  my $self = shift->SUPER::new(@_);
  
  $self->{values} ||= [];
  
  return $self;
}

sub get {
  my ($self, $idx) = @_;
  
  my $value = $self->{values}[$idx - 1];
  
  return $value;
}

sub set {
  my ($self, $idx, $value) = @_;
  
  $self->{values}[$idx - 1] = $value;
  
  return $self;  
}

sub to_string {
  my $self = shift;
  
  my $str = '';
  my $values = $self->values;
  if (@$values) {
    $str .= join(' ', @$values) . "\n";
  }
  
  return $str;
}

sub grep {
  my ($self, $condition) = @_;
  
  if (ref (my $cb = $condition) eq 'CODE') {
    my $array1_values = $self->values;
    my $array2_values = [grep { $cb->($_) } @$array1_values];
    my $array2 = $self->new(values => $array2_values);
    return $array2;
  }
  elsif (ref $condition && $condition->isa('Data::R::Array')) {
    my $array2 = $condition;
    my $array1_names = $self->names->values;
    my $array2_names = $array2->values;
    
    my $array3_values = [];
    for my $array2_name (@$array2_names) {
      my $i = 0;
      for my $array1_name (@$array1_names) {
        if ($array2_name eq $array1_name) {
          push @$array3_values, $self->values->[$i];
          last;
        }
        $i++;
      }
    }
    
    my $array3 = $self->new(values => $array3_values);
    
    return $array3;
  }
}

sub negation {
  my $self = shift;
  
  my $v2 = $self->new;
  my $v1_values = $self->values;
  my $v2_values = $v2->values;
  $v2_values->[$_] = -$v1_values->[$_] for (0 .. @$v1_values - 1);
  
  return $v2;
}

sub add {
  my ($self, $data) = @_;

  my $v3 = $self->new;
  if (ref $data && $data->isa('Data::R::Array')) {
    my $v1_values = $self->values;
    my $v2 = $data;
    my $v2_values = $v2->values;
    my $v3_values = $v3->values;
    
    $v3_values->[$_] = $v1_values->[$_] + $v2_values->[$_] for (0 .. @$v1_values - 1);
  }
  else {
    my $v1_values = $self->values;
    my $v3_values = $v3->values;
    
    $v3_values->[$_] = $v1_values->[$_] + $data for (0 .. @$v1_values - 1);
  }
  
  return $v3;
}

sub subtract {
  my ($self, $data, $reverse) = @_;

  my $v3 = $self->new;
  if (ref $data && $data->isa('Data::R::Array')) {
    my $v1_values = $self->values;
    my $v2 = $data;
    my $v2_values = $v2->values;
    my $v3_values = $v3->values;
    
    $v3_values->[$_] = $v1_values->[$_] - $v2_values->[$_] for (0 .. @$v1_values - 1);
  }
  else {
    my $v1_values = $self->values;
    my $v3_values = $v3->values;

    if ($reverse) {
      $v3_values->[$_] = $data - $v1_values->[$_] for (0 .. @$v1_values - 1);
    }
    else {
      $v3_values->[$_] = $v1_values->[$_] - $data for (0 .. @$v1_values - 1);
    }
  }
  
  return $v3;
}

sub multiply {
  my ($self, $data) = @_;

  my $v3 = $self->new;
  if (ref $data  && $data->isa('Data::R::Array')) {
    my $v1_values = $self->values;
    my $v2 = $data;
    my $v2_values = $v2->values;
    my $v3_values = $v3->values;
    
    $v3_values->[$_] = $v1_values->[$_] * $v2_values->[$_] for (0 .. @$v1_values - 1);
  }
  else {
    my $v1_values = $self->values;
    my $v3_values = $v3->values;
    
    $v3_values->[$_] = $v1_values->[$_] * $data for (0 .. @$v1_values - 1);
  }
  
  return $v3;
}

sub divide {
  my ($self, $data, $reverse) = @_;

  my $v3 = $self->new;
  if (ref $data && $data->isa('Data::R::Array')) {
    my $v1_values = $self->values;
    my $v2 = $data;
    my $v2_values = $v2->values;
    my $v3_values = $v3->values;
    
    $v3_values->[$_] = $v1_values->[$_] / $v2_values->[$_] for (0 .. @$v1_values - 1);
  }
  else {
    my $v1_values = $self->values;
    my $v3_values = $v3->values;
    
    if ($reverse) {
      $v3_values->[$_] = $data / $v1_values->[$_] for (0 .. @$v1_values - 1);
    }
    else {
      $v3_values->[$_] = $v1_values->[$_] / $data for (0 .. @$v1_values - 1);
    }
  }
  
  return $v3;
}

sub raise {
  my ($self, $data, $reverse) = @_;
  
  my $v3 = $self->new;
  if (ref $data && $data->isa('Data::R::Array')) {
    croak 'Not implemented';
  }
  else {
    if ($reverse) {
      croak "Not implemented";
    }
    else {
      my $v1_values = $self->values;
      my $v3_values = $v3->values;
      
      $v3_values->[$_] = $v1_values->[$_] ** $data for (0 .. @$v1_values - 1);
    }
    
    return $v3;
  }
}

1;
