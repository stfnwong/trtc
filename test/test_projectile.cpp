/*
 * TEST_PROJECTILE
 * This is the little parabolic curve sim from the 2nd chapter
 */

#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"

#include "Projectile.hpp"



TEST_CASE("test_projectile", "[test]")
{
    Tuple p_initial_point = create_point(0, 1, 0);
    Tuple p_initial_vel = create_vector(1, 20, 0).norm();

    Tuple e_initial_g = create_vector(0, -0.1, 0);
    Tuple e_initial_w = create_vector(-0.01, 0, 0);

    Projectile init_proj(p_initial_point, p_initial_vel);
    Environment env(e_initial_g, e_initial_w);

    const int MAX_ITERS = 50;
    int cur_iter = 0;

    Projectile cur_proj;

    while(cur_iter < MAX_ITERS) 
    {
        if(cur_iter == 0)
            cur_proj = tick(env, init_proj);
        else
            cur_proj = tick(env, cur_proj);
        cur_iter++;
        std::cout << cur_iter << ": " << cur_proj.toString() << std::endl;

        if(cur_proj.position.y <= 0.0)
            break;
    }

    REQUIRE(cur_iter < (MAX_ITERS / 2));
}
