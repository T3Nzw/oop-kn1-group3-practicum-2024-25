#include "Complex.hpp"
#include "unique_ptr.hpp"
#include "Set.hpp"
#include "Relation.hpp"
#include "Matrix.hpp"

int main() {

  std::cout << std::boolalpha;

  Complex c1{3,4};
  Complex c2(5,-2);

  std::cout << c1 + c2 << '\n';
  std::cout << c2 - c1 << '\n';

  unique_ptr<Complex> ptr1 = make_unique(Complex(1,2));

  std::cout << *ptr1 << '\n';
  std::cout << ptr1->modulus() << '\n';
  std::cout << ptr1->conjugate() << '\n';
  std::cout << ptr1.valid() << '\n';

  Complex* rawPtr = ptr1.release();

  std::cout << ptr1.valid() << '\n';
  std::cout << *rawPtr << '\n';

  unique_ptr<Complex> ptr2(rawPtr);
  std::cout << *ptr2 << '\n';

//можем да го напишем, тъй като rawPtr вече сочи
//към динамично заделената памет и няма как да изгубим достъп до ресурса
  ptr2.release();

//тъй като никой от горните уникални указатели не са
//отговорни за освобождаването на динамично заделената памет,
//трябва да го направим ръчно
  delete rawPtr;

  unique_ptr<Vector<int> > vPtr = make_unique<Vector<int> >({1,2,3,4,5});

  for (size_t i = 0; i < vPtr->size(); ++i) {
    std::cout << (*vPtr)[i] << ' ';
  }
  std::cout << '\n';

  Set<int> set1{1,2,3,4,5};
  Set<int> set2{3,4,1,6};
  Set<int> set3{9,1,2,0,-10,15,42,3,3,1,1,2,4};

  set1.print();
  std::cout << '\n';
  set2.print();
  std::cout << '\n';
  set3.print();
  std::cout << '\n';
  (set1 + set2).print();
  std::cout << '\n';
  (set1 * set2).print();
  std::cout << '\n';
  (set1 - set2).print();
  std::cout << '\n';
  (set1 ^ set2).print();
  std::cout << '\n';

  std::cout << (set1 <= (set1 + set2)) << '\n';
  std::cout << (set1 <= (set1 * set2)) << '\n';
  std::cout << ((set1 ^ set2) == (set2 ^ set1)) << '\n';

  std::cout << set1 * set2 * set3 << '\n';

  Relation<int> r1(set1);
  std::cout << r1.empty() << '\n';

  r1.reflexiveClosure();
  std::cout << r1 << '\n';
  std::cout << r1.isEquivalenceRelation() << '\n';

  r1.insert({1,2});
  r1.insert({5,4});
  r1.insert({4,8});  //8 не е в множеството
  r1.symmetricClosure();
  std::cout << r1 << '\n';
  std::cout << r1.isEquivalenceRelation() << '\n';

  r1.insert({3,1});
  std::cout << r1.isEquivalenceRelation() << '\n';

  std::cout << '\n';
  Matrix<3,3> m1{1,2,3,4,5,6,7};
  std::cout << m1 << '\n';

  Matrix<3,3> m2(m1);
  std::cout << 4*m1+m2*3 << '\n';

  m2 += m1;
  std::cout << m2 << '\n';

  Matrix<2,3> m3{1,2,4,8,16,32};
  Matrix<3,4> m4;

  std::cout << m3*m4;

  return 0;
}