#include "manip.hpp"
#include <cmath>
#include <algorithm>
// you will need cmath and algorithm headers.

namespace ams562_final {

void compute_n2e_adj(const unsigned n, const Triangles &conn,
                     std::vector<std::vector<int>> &adj) {
  // resize adj to n
  adj.resize(n);
  
  // reserve for each of them with a reasonable upper bound
  int i = 0;
  auto get_adj_notes = [&](const std::array<int, 3> &pt){
      adj[pt[0]].push_back(i);
      adj[pt[1]].push_back(i);
      adj[pt[2]].push_back(i);
      i++;
  };
  std::for_each(conn.to_vector().begin(), conn.to_vector().end(), get_adj_notes);
}

void compute_avg_normals(const SphCo &points, const Triangles &conn,
                         const std::vector<std::vector<int>> &n2e_adj,
                         SphCo &nrms) {
  // resize the nrms
  nrms.resize(points.npoints());

  // Step 1: compute the outward normals of spherical triangles
  unsigned s = conn.ntris();
  SphCo f_nrm(s);

  // reference pt and the dist lambda, define the callback that will be
  // triggered inside for_each

  for(unsigned i=0; i<s; i++)
  {
    std::array<int, 3> array_tmp = conn[i];
    std::array<double, 3> pt_tmp1= points[array_tmp[0]];
    std::array<double, 3> pt_tmp2= points[array_tmp[1]];
    std::array<double, 3> pt_tmp3= points[array_tmp[2]];

    //vector AB: (x2-x1, y2-y1,z2-z1), AC(x3-x1, y3-y1, z3-z0)
    double r0 = pt_tmp2[0] - pt_tmp1[0];
    double r1 = pt_tmp2[1] - pt_tmp1[1];
    double r2 = pt_tmp2[2] - pt_tmp1[2];
	
    double s0 = (pt_tmp3[0] - pt_tmp1[0]);
    double s1 = (pt_tmp3[1] - pt_tmp1[1]);
    double s2 = (pt_tmp3[2] - pt_tmp1[2]);
	
    //AB * AC
    double t0 = r1*s2 - r2*s1;
    double t1 = r2*s0 - r0*s2;
    double t2 = r0*s1 - r1*s0;
	
    f_nrm[i][0] = t0;
    f_nrm[i][1] = t1;
    f_nrm[i][2] = t2;
  }
  f_nrm.normalize();

  // Step 2: compute the averaged normal on nodes
  // hint don't forget normalizing the normals
  unsigned t = points.npoints();
  for(unsigned i = 0; i<t; i++)
  {
    std::vector<int> vec_tmp = n2e_adj[i];
    unsigned vec_tmp_size = vec_tmp.size();
    double t0 = 0.0;
    double t1 = 0.0;
    double t2 = 0.0;
    for(unsigned j = 0; j<vec_tmp_size; j++)
    {
      t0 += f_nrm[vec_tmp[j]][0];
      t1 += f_nrm[vec_tmp[j]][1];
      t2 += f_nrm[vec_tmp[j]][2];
    }
    nrms[i][0] = t0;
    nrms[i][1] = t1; 
    nrms[i][2] = t2; 
  }
  nrms.normalize();
  //std::cout<<nrms<<"\n";
}

void compute_errors(const SphCo &exact, const SphCo &num,
                    std::vector<double> &acos_theta) 
{
  // resize the error array
  acos_theta.resize(num.npoints());
  double prod_err = 0.0;

  int i = 0;
  std::array<double, 3> array_tmp;
  auto get_error = [&](const std::array<double, 3> &pt){
      prod_err = 0.0;
      array_tmp = num[i];
      prod_err += pt[0] * array_tmp[0];
      prod_err += pt[1] * array_tmp[1];
      prod_err += pt[2] * array_tmp[2];
      acos_theta.push_back(acos(prod_err));
      i++;
  };
  std::for_each(exact.to_vector().begin(), exact.to_vector().end(), get_error);
}

}  // namespace ams562_final
