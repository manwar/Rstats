template <class T_IN, class T_OUT>
Rstats::Vector* operate_unary_math(T_OUT (*func)(T_IN), Rstats::Vector* v1) {
  
  Rstats::Integer length = v1->get_length();
  
  Rstats::Vector* v_out = Rstats::Vector::new_vector<T_OUT>(length);
  
  Rstats::Util::init_warn();
  for (Rstats::Integer i = 0; i < length; i++) {
    v_out->set_value<T_OUT>(i, (*func)(v1->get_value<T_IN>(i)));
  }
  if (Rstats::Util::get_warn()) {
    Rstats::Util::print_warn_message();
  }
  
  v_out->merge_na_positions(v1->get_na_positions());
  
  return v_out;
}

template <class T_IN>
Rstats::Vector* operate_unary_is(Rstats::Logical (*func)(T_IN), Rstats::Vector* v1) {
  
  Rstats::Integer length = v1->get_length();
  
  Rstats::Vector* v_out = Rstats::Vector::new_vector<Rstats::Logical>(length);

  Rstats::Util::init_warn();
  for (Rstats::Integer i = 0; i < length; i++) {
    if (v1->exists_na_position(i)) {
      v_out->set_value<Rstats::Logical>(i, 0);
    }
    else {
      v_out->set_value<Rstats::Logical>(i, (*func)(v1->get_value<T_IN>(i)));
    }
  }
  if (Rstats::Util::get_warn()) {
    Rstats::Util::print_warn_message();
  }
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* operate_unary_as(T_OUT (*func)(T_IN), Rstats::Vector* v1) {
  
  Rstats::Integer length = v1->get_length();
  
  Rstats::Vector* v_out = Rstats::Vector::new_vector<T_OUT>(length);
  
  Rstats::Util::init_warn();
  for (Rstats::Integer i = 0; i < length; i++) {
    try {
      v_out->set_value<T_OUT>(i, (*func)(v1->get_value<T_IN>(i)));
    }
    catch (...) {
      v_out->add_na_position(i);
    }
  }
  if (Rstats::Util::get_warn()) {
    Rstats::Util::print_warn_message();
  }
  
  v_out->merge_na_positions(v1->get_na_positions());
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* operate_binary_math(T_OUT (*func)(T_IN, T_IN), Rstats::Vector* v1, Rstats::Vector* v2) {

  Rstats::Integer length = v1->get_length();
  Rstats::Vector* v3 = Rstats::Vector::new_vector<T_OUT>(length);

  Rstats::Util::init_warn();
  for (Rstats::Integer i = 0; i < length; i++) {
    v3->set_value<T_OUT>(
      i,
      (*func)(
        v1->get_value<T_IN>(i),
        v2->get_value<T_IN>(i)
      )
    );
  }
  if (Rstats::Util::get_warn()) {
    Rstats::Util::print_warn_message();
  }
  
  v3->merge_na_positions(v1->get_na_positions());
  v3->merge_na_positions(v2->get_na_positions());
  
  return v3;
}

template <class T_IN, class T_OUT>
Rstats::Vector* add(Rstats::Vector* v1, Rstats::Vector* v2) {
  T_OUT (*func)(T_IN, T_IN) = &Rstats::ElementFunc::add;
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_binary_math(func, v1, v2);
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* subtract(Rstats::Vector* v1, Rstats::Vector* v2) {
  T_OUT (*func)(T_IN, T_IN) = &Rstats::ElementFunc::subtract;
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_binary_math(func, v1, v2);
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* multiply(Rstats::Vector* v1, Rstats::Vector* v2) {
  T_OUT (*func)(T_IN, T_IN) = &Rstats::ElementFunc::multiply;
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_binary_math(func, v1, v2);
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* divide(Rstats::Vector* v1, Rstats::Vector* v2) {
  T_OUT (*func)(T_IN, T_IN) = &Rstats::ElementFunc::divide;
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_binary_math(func, v1, v2);
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* remainder(Rstats::Vector* v1, Rstats::Vector* v2) {
  T_OUT (*func)(T_IN, T_IN) = &Rstats::ElementFunc::remainder;
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_binary_math(func, v1, v2);
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* as_character(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::as_character;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_as(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* as_double(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::as_double;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_as(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* as_complex(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::as_complex;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_as(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* as_integer(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::as_integer;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_as(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* as_logical(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::as_logical;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_as(func, v1);
  
  return v_out;
}

template <class T_IN>
Rstats::Vector* is_na(Rstats::Vector* v1) {
  
  Rstats::Integer length = v1->get_length();
  
  Rstats::Vector* v_out = Rstats::Vector::new_vector<Rstats::Logical>(length);
  
  for (Rstats::Integer i = 0; i < length; i++) {
    if (v1->exists_na_position(i)) {
      v_out->set_value<Rstats::Logical>(i, 1);
    }
    else {
      v_out->set_value<Rstats::Logical>(i, 0);
    }
  }
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* sin(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::sin;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* tanh(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::tanh;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* cos(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::cos;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* tan(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::tan;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* sinh(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::sinh;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* cosh(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::cosh;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* log(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::log;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* logb(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::logb;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* log10(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::log10;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* log2(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::log2;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* acos(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::acos;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* acosh(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::acosh;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* asinh(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::asinh;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* atanh(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::atanh;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* Conj(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::Conj;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* asin(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::asin;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* atan(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::atan;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* sqrt(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::sqrt;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* expm1(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::expm1;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* exp(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::exp;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* negate(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::negate;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* Arg(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::Arg;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* abs(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::abs;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* Mod(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::Mod;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* Re(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::Re;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN, class T_OUT>
Rstats::Vector* Im(Rstats::Vector* v1) {
  T_OUT (*func)(T_IN) = &Rstats::ElementFunc::Im;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_math(func, v1);
  
  return v_out;
}

template <class T_IN>
Rstats::Vector* is_infinite(Rstats::Vector* v1) {
  Rstats::Logical (*func)(T_IN) = &Rstats::ElementFunc::is_infinite;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_is(func, v1);
  
  return v_out;
}

template <class T_IN>
Rstats::Vector* is_nan(Rstats::Vector* v1) {
  Rstats::Logical (*func)(T_IN) = &Rstats::ElementFunc::is_nan;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_is(func, v1);
  
  return v_out;
}

template <class T_IN>
Rstats::Vector* is_finite(Rstats::Vector* v1) {
  Rstats::Logical (*func)(T_IN) = &Rstats::ElementFunc::is_finite;
  
  Rstats::Vector* v_out = Rstats::VectorFunc::operate_unary_is(func, v1);
  
  return v_out;
}