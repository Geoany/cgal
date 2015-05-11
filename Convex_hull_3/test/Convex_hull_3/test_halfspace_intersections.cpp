#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Convex_hull_3/dual/halfspace_intersection_3.h>
#include <CGAL/Convex_hull_3/dual/halfspace_intersection_with_constructions_3.h>
#include <CGAL/point_generators_3.h>

#include <list>

typedef CGAL::Exact_predicates_inexact_constructions_kernel   K;
typedef K::Plane_3                                            Plane;
typedef K::Point_3                                            Point;
typedef CGAL::Polyhedron_3<K>                                 Polyhedron_3;

int main (void) {

  // generates supporting planes of the facets of a cube
  std::list<Plane> planes;
  planes.push_back( Plane( 1, 0, 0,-1) ); // x= 1
  planes.push_back( Plane(-1, 0, 0,-1) ); // x=-1
  planes.push_back( Plane( 0, 1, 0,-1) ); // y= 1
  planes.push_back( Plane( 0,-1, 0,-1) ); // y=-1
  planes.push_back( Plane( 0, 0, 1,-1) ); // z= 1
  planes.push_back( Plane( 0, 0,-1,-1) ); // z=-1

  // define polyhedron to hold the intersection
  Polyhedron_3 P1, P2, P3, P4, P5;

  // test halfspace_intersection_3 with a point inside
  CGAL::halfspace_intersection_3(planes.begin(),
                                 planes.end(),
                                 P1,
                                 boost::make_optional(Point(0, 0, 0)) );

  // test halfspace_intersection_3 with non point inside
  CGAL::halfspace_intersection_3(planes.begin(),
                                 planes.end(),
                                 P2);

  // test halfspace_intersection_with_constructions_3 with a point inside
  CGAL::halfspace_intersection_with_constructions_3( planes.begin(),
                                                     planes.end(),
                                                     P3,
                                                     boost::make_optional(Point(0, 0, 0)) );

  // test halfspace_intersection_with_constructions_3 with non point inside
  CGAL::halfspace_intersection_with_constructions_3( planes.begin(),
                                                     planes.end(),
                                                     P4);

  // test halfspace_intersection_with_constructions_3 with non point inside but with the kernel
  CGAL::halfspace_intersection_with_constructions_3( planes.begin(),
                                                     planes.end(),
                                                     P5,
                                                     boost::optional<Point>(),
                                                     K());

  assert(P1.size_of_vertices()==8 && P1.size_of_facets()==6);
  assert(P2.size_of_vertices()==8 && P2.size_of_facets()==6);
  assert(P3.size_of_vertices()==8 && P3.size_of_facets()==6);
  assert(P4.size_of_vertices()==8 && P4.size_of_facets()==6);
  assert(P5.size_of_vertices()==8 && P5.size_of_facets()==6);

  return 0;
}

