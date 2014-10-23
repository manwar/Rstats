namespace Rstats {
  // Rstats::Perl
  namespace Perl {
    
    SV* new_ref(SV* sv) {
      return sv_2mortal(newRV_inc(sv));
    }

    SV* new_ref(AV* av) {
      return sv_2mortal(newRV_inc((SV*)av));
    }

    SV* new_ref(HV* hv) {
      return sv_2mortal(newRV_inc((SV*)hv));
    }
    
    I32 get_iv (SV* sv) {
      return SvIV(sv);
    }
    
    U32 get_uv(SV* sv) {
      return SvUV(sv);
    }

    double get_nv(SV* sv) {
      return SvNV(sv);
    }
      
    char* get_pv(SV* sv) {
      return SvPV_nolen(sv);
    }

    SV* new_scalar(SV* sv) {
      return sv_2mortal(newSVsv(sv));
    }

    SV* new_scalar(const char* pv) {
      return sv_2mortal(newSVpvn(pv, strlen(pv)));
    }
    
    SV* new_scalar_iv(I32 iv) {
      return sv_2mortal(newSViv(iv));
    }

    SV* new_scalar_uv(U32 uv) {
      return sv_2mortal(newSVuv(uv));
    }
    
    SV* new_scalar_nv(double nv) {
      return sv_2mortal(newSVnv(nv));
    }
    
    AV* new_array() {
      return (AV*)sv_2mortal((SV*)newAV());
    }
    
    SV* new_array_ref() {
      return sv_2mortal(newRV_inc((SV*)new_array()));
    }
    
    HV* new_hash() {
      return (HV*)sv_2mortal((SV*)newHV());
    }

    SV* new_hash_ref() {
      return sv_2mortal(newRV_inc((SV*)new_hash()));
    }

    SV* scalar_deref(SV* ref) {
      if (SvROK(ref)) {
        return SvRV(ref);
      }
      else {
        croak("Can't derefernce");
      }
    }
    
    AV* array_deref(SV* ref) {
      if (SvROK(ref)) {
        return (AV*)SvRV(ref);
      }
      else {
        croak("Can't derefernce");
      }
    }
    
    void array_extend(AV* av, I32 key) {
      return av_extend(av, key);
    }

    void array_extend(SV* av_ref, I32 key) {
      AV* av = array_deref(av_ref);
      return av_extend(av, key);
    }
    
    I32 array_length (AV* av) {
      return av_len(av) + 1;
    }

    I32 array_length (SV* av_ref) {
      return av_len(array_deref(av_ref)) + 1;
    }
    
    SV* array_fetch(AV* av, I32 pos) {
      SV** const element_ptr = av_fetch(av, pos, FALSE);
      SV* const element = element_ptr ? *element_ptr : &PL_sv_undef;
      
      return element;
    }
    
    SV* array_fetch(SV* av_ref, I32 pos) {
      AV* av = array_deref(av_ref);
      SV** const element_ptr = av_fetch(av, pos, FALSE);
      SV* const element = element_ptr ? *element_ptr : &PL_sv_undef;
      
      return element;
    }

    HV* hash_deref(SV* ref) {
      if (SvROK(ref)) {
        return (HV*)SvRV(ref);
      }
      else {
        croak("Can't derefernce");
      }
    }
    
    SV* hash_fetch(HV* hv, const char* key) {
      SV** const element_ptr = hv_fetch(hv, key, strlen(key), FALSE);
      SV* const element = element_ptr ? *element_ptr : &PL_sv_undef;
      
      return element;
    }

    SV* hash_fetch(HV* hv, SV* key_sv) {
      return hash_fetch(hv, get_pv(key_sv));
    }
    
    SV* hash_fetch(SV* hv_ref, const char* key) {
      HV* hv = hash_deref(hv_ref);
      SV** const element_ptr = hv_fetch(hv, key, strlen(key), FALSE);
      SV* const element = element_ptr ? *element_ptr : &PL_sv_undef;
      
      return element;
    }

    SV* hash_fetch(SV* hv_ref, SV* key_sv) {
      return hash_fetch(hv_ref, get_pv(key_sv));
    }
    
    void array_store(AV* av, I32 pos, SV* element) {
      av_store(av, pos, SvREFCNT_inc(element));
    }
    
    void array_store(SV* av_ref, I32 pos, SV* element) {
      AV* av = array_deref(av_ref);
      av_store(av, pos, SvREFCNT_inc(element));
    }

    SV* array_copy(SV* av_ref_sv) {
      SV* new_array_ref_sv = new_array_ref();
      
      for (I32 i = 0; i < array_length(av_ref_sv); i++) {
        array_store(new_array_ref_sv, i, new_scalar(array_fetch(av_ref_sv, i)));
      }
      
      return new_array_ref_sv;
    }
    
    void hash_store(HV* hv, const char* key, SV* element) {
      hv_store(hv, key, strlen(key), SvREFCNT_inc(element), FALSE);
    }

    void hash_store(SV* hv_ref, const char* key, SV* element) {
      HV* hv = hash_deref(hv_ref);
      hv_store(hv, key, strlen(key), SvREFCNT_inc(element), FALSE);
    }
    
    void array_push(AV* av, SV* sv) {
      av_push(av, SvREFCNT_inc(sv));
    }
    
    void array_push(SV* av_ref, SV* sv) {
      av_push(array_deref(av_ref), SvREFCNT_inc(sv));
    }

    void array_unshift(AV* av, SV* sv) {
      av_unshift(av, 1);
      array_store(av, (I32)0, sv);
    }
    
    void array_unshift(SV* av_ref, SV* sv) {
      av_unshift(array_deref(av_ref), 1);
      array_store(array_deref(av_ref), 0, sv);
    }

    template <class X> X to_c_obj(SV* perl_obj_ref) {
      SV* perl_obj = SvROK(perl_obj_ref) ? SvRV(perl_obj_ref) : perl_obj_ref;
      size_t obj_addr = SvIV(perl_obj);
      X c_obj = INT2PTR(X, obj_addr);
      
      return c_obj;
    }

    template <class X> SV* to_perl_obj(X c_obj, const char* class_name) {
      I32 obj_addr = PTR2IV(c_obj);
      SV* obj_addr_sv = new_scalar_iv(obj_addr);
      SV* obj_addr_sv_ref = new_ref(obj_addr_sv);
      SV* perl_obj = sv_bless(obj_addr_sv_ref, gv_stashpv(class_name, 1));
      
      return perl_obj;
    }
  };
  
  // Rstats::ElementsType
  namespace ElementsType {
    enum Enum {
      LOGICAL = 1,
      INTEGER = 2,
      DOUBLE = 4,
      COMPLEX = 8,
      CHARACTER = 16
    };
  }
  
  namespace Values {
    // Rstats::Values::Character
    typedef std::vector<SV*> Character;
    
    // Rstats::Values::Complex
    typedef std::vector<std::complex<double> > Complex;
    
    // Rstats::Values::Double
    typedef std::vector<double> Double;
    
    // Rstats::Values::Integer
    typedef std::vector<I32> Integer;
  }

  // Rstats::Elements
  class Elements {
    private:
    Rstats::ElementsType::Enum type;
    void* values;
    std::map<I32, I32> na_positions;
    
    public:
    
    ~Elements () {
      I32 size = this->get_size();
      if (this->get_type() == Rstats::ElementsType::INTEGER || this->get_type() == Rstats::ElementsType::LOGICAL) {
        Rstats::Values::Integer* values = this->get_integer_values();
        delete values;
      }
      else if (this->get_type() == Rstats::ElementsType::DOUBLE) {
        Rstats::Values::Double* values = this->get_double_values();
        delete values;
      }
      else if (this->get_type() == Rstats::ElementsType::COMPLEX) {
        Rstats::Values::Complex* values = this->get_complex_values();
        delete values;
      }
      else if (this->get_type() == Rstats::ElementsType::CHARACTER) {
        Rstats::Values::Character* values = this->get_character_values();
        for (I32 i = 0; i < size; i++) {
          if ((*values)[i] != NULL) {
            SvREFCNT_dec((*values)[i]);
          }
        }
        delete values;
      }
    }
    
    Rstats::Values::Character* get_character_values() {
      return (Rstats::Values::Character*)this->values;
    }
    
    Rstats::Values::Complex* get_complex_values() {
      return (Rstats::Values::Complex*)this->values;
    }
    
    Rstats::Values::Double* get_double_values() {
      return (Rstats::Values::Double*)this->values;
    }
    
    Rstats::Values::Integer* get_integer_values() {
      return (Rstats::Values::Integer*)this->values;
    }
    
    Rstats::ElementsType::Enum get_type() {
      return this->type;
    }
    
    void add_na_position (I32 position) {
      this->na_positions[position] = 1;
    }

    bool exists_na_position (I32 position) {
      return this->na_positions.count(position);
    }
    
    void merge_na_positions (Rstats::Elements* elements) {
      for(std::map<I32, I32>::iterator it = elements->na_positions.begin(); it != elements->na_positions.end(); ++it) {
        this->add_na_position(it->first);
      }
    }
    
    I32 get_size () {
      if (this->type == Rstats::ElementsType::CHARACTER) {
        return this->get_character_values()->size();
      }
      else if (this->type == Rstats::ElementsType::COMPLEX) {
        return this->get_complex_values()->size();
      }
      else if (this->type == Rstats::ElementsType::DOUBLE) {
        return this->get_double_values()->size();
      }
      else if (this->type == Rstats::ElementsType::INTEGER || Rstats::ElementsType::LOGICAL) {
        return this->get_integer_values()->size();
      }
    }

    static Rstats::Elements* new_character(I32 size) {

      Rstats::Elements* elements = new Rstats::Elements;
      elements->values = new Rstats::Values::Character(size, NULL);
      elements->type = Rstats::ElementsType::CHARACTER;
      
      return elements;
    }

    static Rstats::Elements* new_character(I32 size, SV* str_sv) {

      Rstats::Elements* elements = Rstats::Elements::new_character(size);
      for (I32 i = 0; i < size; i++) {
        elements->set_character_value(i, str_sv);
      }
      elements->type = Rstats::ElementsType::CHARACTER;
      
      return elements;
    }

    SV* get_character_value(I32 pos) {
      SV* value = (*this->get_character_values())[pos];
      if (value == NULL) {
        return NULL;
      }
      else {
        return Rstats::Perl::new_scalar(value);
      }
    }
    
    void set_character_value(I32 pos, SV* value) {
      if (value != NULL) {
        SvREFCNT_dec((*this->get_character_values())[pos]);
      }
      
      SV* new_value = Rstats::Perl::new_scalar(value);
      SvREFCNT_inc(new_value);
      (*this->get_character_values())[pos] = new_value;
    }

    static Rstats::Elements* new_complex(I32 size) {
      
      Rstats::Elements* elements = new Rstats::Elements;
      elements->values = new Rstats::Values::Complex(size, std::complex<double>(0, 0));
      elements->type = Rstats::ElementsType::COMPLEX;
      
      return elements;
    }
        
    static Rstats::Elements* new_complex(I32 size, std::complex<double> z) {
      
      Rstats::Elements* elements = new Rstats::Elements;
      elements->values = new Rstats::Values::Complex(size, z);
      elements->type = Rstats::ElementsType::COMPLEX;
      
      return elements;
    }

    std::complex<double> get_complex_value(I32 pos) {
      return (*this->get_complex_values())[pos];
    }
    
    void set_complex_value(I32 pos, std::complex<double> value) {
      (*this->get_complex_values())[pos] = value;
    }
    
    static Rstats::Elements* new_double(I32 size) {
      Rstats::Elements* elements = new Rstats::Elements;
      elements->values = new Rstats::Values::Double(size);
      elements->type = Rstats::ElementsType::DOUBLE;
      
      return elements;
    }

    static Rstats::Elements* new_double(I32 size, double value) {
      Rstats::Elements* elements = new Rstats::Elements;
      elements->values = new Rstats::Values::Double(size, value);
      elements->type = Rstats::ElementsType::DOUBLE;
      
      return elements;
    }
    
    double get_double_value(I32 pos) {
      return (*this->get_double_values())[pos];
    }
    
    void set_double_value(I32 pos, double value) {
      (*this->get_double_values())[pos] = value;
    }

    static Rstats::Elements* new_integer(I32 size) {
      
      Rstats::Elements* elements = new Rstats::Elements;
      elements->values = new Rstats::Values::Integer(size);
      elements->type = Rstats::ElementsType::INTEGER;
      
      return elements;
    }

    static Rstats::Elements* new_integer(I32 size, I32 value) {
      
      Rstats::Elements* elements = new Rstats::Elements;
      elements->values = new Rstats::Values::Integer(size, value);
      elements->type = Rstats::ElementsType::INTEGER;
      
      return elements;
    }

    I32 get_integer_value(I32 pos) {
      return (*this->get_integer_values())[pos];
    }
    
    void set_integer_value(I32 pos, I32 value) {
      (*this->get_integer_values())[pos] = value;
    }
    
    static Rstats::Elements* new_logical(I32 size) {
      Rstats::Elements* elements = new Rstats::Elements;
      elements->values = new Rstats::Values::Integer(size);
      elements->type = Rstats::ElementsType::LOGICAL;
      
      return elements;
    }

    static Rstats::Elements* new_logical(I32 size, I32 value) {
      Rstats::Elements* elements = new Rstats::Elements;
      elements->values = new Rstats::Values::Integer(size, value);
      elements->type = Rstats::ElementsType::LOGICAL;
      
      return elements;
    }
    
    static Rstats::Elements* new_true() {
      return new_logical(1, 1);
    }

    static Rstats::Elements* new_false() {
      return new_logical(1, 0);
    }
    
    static Rstats::Elements* new_NaN() {
      return  Rstats::Elements::new_double(1, NAN);
    }

    static Rstats::Elements* new_negativeInf() {
      return Rstats::Elements::new_double(1, -(INFINITY));
    }
    
    static Rstats::Elements* new_Inf() {
      return Rstats::Elements::new_double(1, INFINITY);
    }
    
    static Rstats::Elements* new_NA() {
      Rstats::Elements* elements = new Rstats::Elements;
      elements->values = new Rstats::Values::Integer(1, 0);
      elements->type = Rstats::ElementsType::LOGICAL;
      elements->add_na_position(0);
      
      return elements;
    }
  };
  
  // Rstats::ElementsFunc
  namespace ElementsFunc {
    
    Rstats::Elements* is_infinite(Rstats::Elements* elements) {
      
      I32 size = elements->get_size();
      Rstats::Elements* rets;
      if (elements->get_type() == Rstats::ElementsType::DOUBLE) {
        rets = Rstats::Elements::new_logical(size);
        Rstats::Values::Double* values = elements->get_double_values();
        Rstats::Values::Integer* rets_values = rets->get_integer_values();
        for (I32 i = 0; i < size; i++) {
          if(std::isinf((*values)[i])) {
            (*rets_values)[i] = 1;
          }
          else {
            (*rets_values)[i] = 0;
          }
        }
      }
      else {
        rets = Rstats::Elements::new_logical(size, 0);
      }
      
      return rets;
    }

    Rstats::Elements* is_nan(Rstats::Elements* elements) {
      I32 size = elements->get_size();
      Rstats::Elements* rets = Rstats::Elements::new_logical(size);
      if (elements->get_type() == Rstats::ElementsType::DOUBLE) {
        Rstats::Values::Double* values = elements->get_double_values();
        Rstats::Values::Integer* rets_values = rets->get_integer_values();
        for (I32 i = 0; i < size; i++) {
          if(std::isnan((*values)[i])) {
            (*rets_values)[i] = 1;
          }
          else {
            (*rets_values)[i] = 0;
          }
        }
      }
      else {
        rets = Rstats::Elements::new_logical(size, 0);
      }
      
      return rets;
    }

    Rstats::Elements* is_finite(Rstats::Elements* elements) {
      
      I32 size = elements->get_size();
      Rstats::ElementsType::Enum type = elements->get_type();
      Rstats::Elements* rets;
      if (type == Rstats::ElementsType::INTEGER) {
        rets = Rstats::Elements::new_logical(size, 1);
      }
      else if (type == Rstats::ElementsType::DOUBLE) {
        Rstats::Values::Double* values = elements->get_double_values();
        rets = Rstats::Elements::new_logical(size);
        Rstats::Values::Integer* rets_values = rets->get_integer_values();
        for (I32 i = 0; i < size; i++) {
          if (std::isfinite((*values)[i])) {
            (*rets_values)[i] = 1;
          }
          else {
            (*rets_values)[i] = 0;
          }
        }
      }
      else {
        rets = Rstats::Elements::new_logical(size, 0);
      }
      
      return rets;
    }
  }
}
