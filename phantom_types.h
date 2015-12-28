#ifndef PHANTOM_TYPE_H
#define PHANTOM_TYPE_H

template <typename T, typename Meaning>
struct Explicit
{
  //! Default constructor does not initialize the value.
  Explicit()
  { }

  //! Construction from a fundamental value.
  Explicit(T value)
    : value(value)
  { }

  //! Implicit conversion back to the fundamental data type.
  inline operator T () const { return value; }

  //! The actual fundamental value.
  T value;
};

#endif //PHANTOM_TYPE_H
