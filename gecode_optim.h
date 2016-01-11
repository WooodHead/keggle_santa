#ifndef GECODEOPTIM_H
#define GECODEOPTIM_H

#include <algorithm>

#include "Solution.h"
#include "Route.h"

#include <gecode/driver.hh>
#include <gecode/int.hh>
#include <gecode/minimodel.hh>
#include <gist.hh>
#include <gecode/search.hh>
using namespace Gecode;

//FloatMinimizeSpace

class SendMoreMoney : public Space {
protected:
  IntVarArray l;
public:
  SendMoreMoney(void) : l(*this, 8, 0, 9) {
    IntVar s(l[0]), e(l[1]), n(l[2]), d(l[3]),
           m(l[4]), o(l[5]), r(l[6]), y(l[7]);
    // no leading zeros
    rel(*this, s, IRT_NQ, 0);
    rel(*this, m, IRT_NQ, 0);
    // all letters distinct
    distinct(*this, l);
    // linear equation
    IntArgs c(4+4+5); IntVarArgs x(4+4+5);
    c[0]=1000; c[1]=100; c[2]=10; c[3]=1;
    x[0]=s;    x[1]=e;   x[2]=n;  x[3]=d;
    c[4]=1000; c[5]=100; c[6]=10; c[7]=1;
    x[4]=m;    x[5]=o;   x[6]=r;  x[7]=e;
    c[8]=-10000; c[9]=-1000; c[10]=-100; c[11]=-10; c[12]=-1;
    x[8]=m;      x[9]=o;     x[10]=n;    x[11]=e;   x[12]=y;
    linear(*this, c, x, IRT_EQ, 0);
    // post branching
    branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
  }
  // search support
  SendMoreMoney(bool share, SendMoreMoney& s) : Space(share, s) {
    l.update(*this, share, s.l);
  }
  virtual Space* copy(bool share) {
    return new SendMoreMoney(share,*this);
  }
  // print solution
  inline
  void print(void) const {
    std::cout << l << std::endl;
  }

  inline
  void print(ostream& stream) const{
      stream << l << endl;
  }
};





//FloatMinimizeSpace
// Space
// IntMinimizeSpace
//using RouteSpaceBaseClass = IntMinimizeSpace;
using RouteSpaceBaseClass = Space;

inline
void l_changed(Space& s){
  cout << "aaa" << endl;
}

class RouteOptimProblem{
public:
    RouteOptimProblem(GlobalGiftData g_data, Route & r): r(r), g_data(g_data){
        dist_values = init_distance_matrix();
    }

    double TotalWeight(){
        //return round(r.Weight());
        return r.Weight();
    }

    vector<double> Weights(){
//        vector<int> res;
//        auto __w = r.GenWeights();
//        for(auto w: __w){ res.push_back( round(w) ); };
//        return res;
        return r.GenWeights();
    }

    vector<double> init_distance_matrix(){
        vector<Location> loc;
        loc.push_back(north_pole);
        for(auto g_id: r){
            loc.push_back(g_data[g_id].Loc());
        };

        auto n = loc.size();
        auto res_size = n*n;


        vector<double> res(res_size);
//        double* res = new double[res_size];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                auto index = i*n + j;

                auto loc1 = loc[i];
                auto loc2 = loc[j];

                res[index] = Dist(loc1, loc2);
            }

        return res;
    }

    inline int size(){return r.size();}



    vector<double> dist_values;
    Route & r;
    GlobalGiftData g_data;
};

class RouteSpace : public RouteSpaceBaseClass{
private:

protected:
  IntVarArray l;
  IntVar weariness;
//  FloatVarArray weariness;

//  Route & r;
//  GlobalGiftData g_data;
  RouteOptimProblem problem;
public:
  RouteSpace(RouteOptimProblem problem):
      //r(r),
      //g_data(g_data),
      problem(problem),

      l(*this, problem.size(), 0, problem.size()),
      weariness(*this, 0, max_weariness(problem.r))
  {
      auto n = problem.size();
//


      //IntArg total_weight = problem.TotalWeight();

      //int* kkk = new int[]{1,2,3,4,5};

      //auto __route_weights = problem.Weights();
      int* __route_weights = new int[5]{1,2,3,4,5};

      IntArgs r_weights(5, __route_weights);

      IntVarArgs weights(problem.size());

//      for (int i = 0; i < problem.size(); ++i) {

//        element(*this, r_weights, i, weights[i]);
//      }


    //      Gecode::Matrix<IntVarArgs> m_dist(distances, n,n);
      //IntVar sum_dist = expr(*this, )

////      IntVar dist_var;
////      IntVar index = expr(*this, l[0]*n + l[1] );
////      element(*this, distances, index, dist_var);



//      IntArgs k(n);
//      for (int i = 0; i < n; ++i) {
//          if(i==0)
//            k[i] =  m_dist(0, l[i]);
//          else
//            k[i] = m_dist(l[i-1], l[i]);
//      };




//      l[0] = expr(*this, 0);

      distinct(*this, l);
      circuit(*this, l);

      //rel(*this, l[0], IRT_EQ, 0);

      //rel(*this, l[0] == 0);
      //circuit(*this, l);
      //rel(*this, );


//      weariness = expr(*this, 5);


//      auto __distances = problem.dist_values;
//      IntArgs distances(__distances.begin(), __distances.end());

//      IntVarArgs dist_var(n);
//      IntVarArgs index(n);
//      for (int i = 0; i < n; ++i) {
//        if(i==0)
//            index[i] =  expr(*this, l[i]);
//        else
//            index[i] = expr(*this, l[i-1]*n+l[i] );

//        element(*this, distances, index[i], dist_var[i]);
//      };

//      weariness = expr(*this, sum(dist_var) );


      Gecode::wait(*this, l, &l_changed);

      // post branching
      branch(*this, l, INT_VAR_SIZE_MIN(), INT_VAL_MIN());
  }

  // search support
  RouteSpace(bool share, RouteSpace& s) : RouteSpaceBaseClass(share, s),
                                          problem(s.problem)
                                          {
    l.update(*this, share, s.l);
    weariness.update(*this, share, s.weariness);
  }

//  virtual IntVar cost(void) const  {
//    return weariness;
//  }

  virtual RouteSpaceBaseClass* copy(bool share) {
    return new RouteSpace(share, *this);
  }

  // print solution
  inline
  void print(void) const {
    std::cout << l << std::endl;
    std::cout << weariness << std::endl;
  }

  inline
  void print(ostream& stream) const{
      stream << l << endl;
      stream << weariness << std::endl;
  }
private:
//    inline
//    int f_round(FloatType fval){
//        return round(fval);
//    }


//    inline vector<int> gen_distances(const Route & r){
//        vector<int> res;
//        auto f_dist = r.GenDistances();
//        for(auto f_d: f_dist) res.push_back(f_round(f_d));
//        return res;
//    }

    inline
    int max_weariness(Route & route){
         auto res = round(route.Weight()*route.Distance());
         return res;
    }

//    inline
//    vector<int> get_costs(){

//    }

};


inline
int gecode_app(GlobalGiftData g_data,  Route & route){
    auto obj_initial = route_evaluation(g_data, route);

    using ModelType = RouteSpace;

    RouteOptimProblem problem(g_data, route);

    ModelType* m = new ModelType(problem);
    Gist::Print<ModelType> p("Print solution");
    //Gist::VarComparator<SendMoreMoney> c("Compare nodes");
    Gist::Options o;
    o.inspect.click(&p);
    //o.inspect.compare(&c)

    //Gist::dfs(m, o);
    Gist::bab(m, o);

    // create model and search engine
//      SendMoreMoney* m = new SendMoreMoney;
//      DFS<SendMoreMoney> e(m);
//      delete m;
//      // search and print all solutions
//      while (SendMoreMoney* s = e.next()) {
//        s->print();
//        delete s;
//      }
      return 0;
}

#endif // GECODEOPTIM_H
