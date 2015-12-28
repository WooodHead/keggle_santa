#ifndef GECODESUPPORT_H
#define GECODESUPPORT_H

#include <iostream>

#include <gecode/driver.hh>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>

using namespace std;

using namespace Gecode;

/**
 * \name %Graph specification for independent sets
 *
 * \relates IndSet
 */
//@{
/// %Graph specification
class Graph {
public:
    const int  n_v; ///< Number of vertices
    const int  n_e; ///< Number of edges
    const int* e;   ///< Arrays of edges (as vertex pairs)
    Graph(const int n_v0, const int n_e0, const int* e0)
            : n_v(n_v0), n_e(n_e0), e(e0) {}
};

const int e_20_10[] = {
        0, 4,  2,12,  12,14,  18,19,   7,10,
        9,12,  5,11,   6,15,   3,18,   7,16
};

const Graph g_20_10(20,10,e_20_10);

const int e_40_20[] = {
        21,30,   11,30,   19,38,   20,25,   11,24,
        20,33,    8,39,    4, 5,    6,16,    5,32,
        0, 9,    5,24,   25,28,   36,38,   14,20,
        19,25,   11,22,   13,30,    7,36,   15,33
};

const Graph g_40_20(40, 20, e_40_20);
//@}


/**
 * \brief %Example: Independent sets in a graph
 *
 * \ingroup Example
 *
 */
class IndSet : public IntMaximizeScript {
protected:
    /// %Graph used
    const Graph& g;
    /// Whether vertex included in independent set
    BoolVarArray v;
    /// How many elements has indipendent set
    IntVar       k;
public:
    /// Actual model
    IndSet(const SizeOptions& opt)
            : IntMaximizeScript(opt),
              g(opt.size() == 0 ?  g_20_10 : g_40_20),
              v(*this,g.n_v,0,1), k(*this,0,g.n_v) {
        const int* e = g.e;
        for (int i = g.n_e; i--; ) {
            const int* e1 = e++; const int* e2 = e++;
            rel(*this, v[*e1], BOT_AND, v[*e2], 0);
        }
        linear(*this, v, IRT_EQ, k);
        branch(*this, v, INT_VAR_NONE(), INT_VAL_MIN());
    }

    /// Constructor for cloning \a s
    IndSet(bool share, IndSet& s) : IntMaximizeScript(share,s), g(s.g) {
        v.update(*this, share, s.v);
        k.update(*this, share, s.k);
    }
    /// Copy during cloning
    virtual Space*
    copy(bool share) {
        return new IndSet(share,*this);
    }
    /// Print solution
    virtual void
    print(std::ostream& os) const {
        os << "\tk = " << k << std::endl
        << "\tv[] = " << v << std::endl;
    }
    /// Return solution cost
    virtual IntVar cost(void) const {
        return k;
    }
};


inline
int gecode_main() {

    SizeOptions opt("IndSet");
    opt.solutions(0);
    opt.size(1);
    opt.iterations(2000);
    //opt.parse(argc,argv);
    IntMaximizeScript::run<IndSet,BAB,SizeOptions>(opt);
    return 0;

//    cout << "Hello, World!" << endl;
//    return 0;
}

#endif // GECODESUPPORT_H
