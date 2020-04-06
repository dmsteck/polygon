//
// Created by daniel on 04/04/2020.
//

#include <boost/polygon/polygon.hpp>

#include <iostream>

static void bad() {
    const boost::polygon::point_data<int> triangles[][3] = {
        {{-7273739, 1362950}, {-7273144, 1362356}, {-3077455, -2833333}},
        {{-490017, -3840545}, {-2888380, -1442182}, {-6168936, 1838374}},
        {{-3078718, -2832071}, {-3078274, -2832514}, {-2288161, -2042401}},
    };

    boost::polygon::polygon_set_data<int> polygon_set;
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(triangles[0]), std::end(triangles[0])));
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(triangles[1]), std::end(triangles[1])));
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(triangles[2]), std::end(triangles[2])));

    // Workaround
    //using Point = boost::polygon::point_data<int>;
    //using Edge = std::pair<Point, Point>;
    //using Element = std::pair<Edge, int>;
    //polygon_set.clean();
    //polygon_set.insert(Element{Edge{Point{0, 0}, Point{0, 0}}, 1});

    std::vector<boost::polygon::polygon_with_holes_data<int>> output;
    polygon_set.get(output);
}

// The input is the result of cleaning the triangles of death
static void test_clean() {
    using Point = boost::polygon::point_data<int>;
    using Edge = std::pair<Point, Point>;
    using Element = std::pair<Edge, int>;

    // Hourglass shape
    const Element elements[] = {{Edge{Point{-7273739, 1362950}, Point{-3078718, -2832071}}, 1},
                                {Edge{Point{-7273739, 1362950}, Point{-7273144, 1362356}}, -1},
                                {Edge{Point{-7273144, 1362356}, Point{-3078718, -2832071}}, -1},
                                {Edge{Point{-3078718, -2832071}, Point{-3078275, -2832514}}, 1},
                                {Edge{Point{-3078718, -2832071}, Point{-2288161, -2042401}}, -1},
                                {Edge{Point{-3078275, -2832514}, Point{-3077455, -2833333}}, 1},
                                {Edge{Point{-3078274, -2832514}, Point{-3077455, -2833333}}, -1},
                                {Edge{Point{-3078274, -2832514}, Point{-2288162, -2042401}}, 1},
                                {Edge{Point{-2288162, -2042401}, Point{-2288161, -2042401}}, 1},
    };

    boost::polygon::polygon_set_data<int> polygon_set;
    polygon_set.insert(std::begin(elements), std::end(elements));

    polygon_set.clean();

    std::vector<boost::polygon::polygon_with_holes_data<int>> output;
    polygon_set.get(output);
}

// Test to verify that polygon_set_data::clean() removes hourglass intersections
static void hourglass() {
    using Point = boost::polygon::point_data<int>;
    using Edge = std::pair<Point, Point>;
    using Element = std::pair<Edge, int>;

    // Hourglass shape
    const Element bottom = {Edge{Point{0, 0}, Point{2, 0}}, 1};
    const Element northwest = {Edge{Point{2, 0}, Point{0, 2}}, 1};
    const Element northeast = {Edge{Point{0, 0}, Point{2, 2}}, -1};
    const Element top = {Edge{Point{0, 2}, Point{2, 2}}, 1};

    boost::polygon::polygon_set_data<int> polygon_set;
    polygon_set.insert(bottom);
    polygon_set.insert(northwest);
    polygon_set.insert(northeast);
    polygon_set.insert(top);

    polygon_set.clean();

    std::vector<boost::polygon::polygon_with_holes_data<int>> output;
    polygon_set.get(output);

    std::cout << "test succeeded" << std::endl;
}

static void test() {
    const boost::polygon::point_data<int> triangles[][3] = {
        {{-7273739, 1362950}, {-7273144, 1362356}, {-3077455, -2833333}},
        {{-490017, -3840545}, {-2888380, -1442182}, {-6168936, 1838374}},
        {{-3078718, -2832071}, {-3078274, -2832514}, {-2288161, -2042401}},
    };

    boost::polygon::polygon_set_data<int> polygon_set;
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(triangles[0]), std::end(triangles[0])));
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(triangles[1]), std::end(triangles[1])));
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(triangles[2]), std::end(triangles[2])));

    polygon_set.clean();

    std::cout << "test succeeded" << std::endl;
}

static void intersection() {
    using compute_intersection_pack = boost::polygon::scanline_base<int>::compute_intersection_pack;

    using Point = boost::polygon::point_data<int>;
    using HalfEdge = std::pair<Point, Point>;

    const HalfEdge he1{Point{-6168936, 1838374}, Point{-490017, -3840545}};
    const HalfEdge he2{Point{-3078274, -2832514}, Point{-2288161, -2042401}};

    Point intersection;
    compute_intersection_pack{}.compute_exact_intersection(intersection, he1, he2);

    std::cout << intersection.x() << ", " << intersection.y() << std::endl;
}

static void intersects_grid() {
    using Point = boost::polygon::point_data<int>;
    using HalfEdge = std::pair<Point, Point>;

    const Point pt{-2288162, -2042401};
    const HalfEdge he{Point{-3078718, -2832071}, Point{-2288161, -2042401}};

    const bool result = boost::polygon::scanline_base<int>::intersects_grid(pt, he);

    std::cout << "Result: " << std::boolalpha << result << std::endl;
}

static void weird() {
    const boost::polygon::point_data<int> tri1[] = {{-7273739, 1362950}, {-7273144, 1362356}, {-3077455, -2833333}};
    const boost::polygon::point_data<int> tri2[] = {{-490017, -3840545}, {-2888380, -1442182}, {-6168936, 1838374}};
    const boost::polygon::point_data<int> tri3[] = {{-3078718, -2832071}, {-3078274, -2832514}, {-2288161, -2042401}};

    boost::polygon::polygon_set_data<int> polygon_set;
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(tri1), std::end(tri1)));
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(tri2), std::end(tri2)));
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(tri3), std::end(tri3)));

    std::vector<boost::polygon::polygon_with_holes_data<int>> output;
    polygon_set.get(output);
}

static void good() {
    const boost::polygon::point_data<int> triangles[][3] = {
        {{-7273739, 1362950}, {-7273144, 1362356}, {-3077455, -2833333}},
        // first x-coordinate shifted by one to avoid collinearity
        {{-490017, -3840544}, {-2888380, -1442182}, {-6168936, 1838374}},
        {{-3078718, -2832071}, {-3078274, -2832514}, {-2288161, -2042401}},
    };

    boost::polygon::polygon_set_data<int> polygon_set;
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(triangles[0]), std::end(triangles[0])));
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(triangles[1]), std::end(triangles[1])));
    polygon_set.insert(boost::polygon::polygon_data<int>(std::begin(triangles[2]), std::end(triangles[2])));

    std::vector<boost::polygon::polygon_with_holes_data<int>> output;
    polygon_set.get(output);
}

int main() {
    bad();
}
