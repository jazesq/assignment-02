#include <random>
// TODO: `#include`s for other system headers, if necessary

#include "neighborhood.h"
#include "constants.h"


// TODO: `#include`s for other local headers, if necessary

// ----------------------------------------------------------------------------
// local helper functions

/**
 * Notes:
 * - If you like, you can start reading about what this "unnamed `namespace`"
 *   is for [here](http://www.comeaucomputing.com/techtalk/#nostatic).
 */
namespace {

    /**
     * Return a uniformly distributed random number in the range [low, high]
     * using the Mersenne Twister engine, seeded with (ideally) the hardware
     * random device.
     *
     * Because `rand()` (and especially `rand() % ...`) maybe shouldn't be
     * used, if we can avoid it:
     * [`rand()` considered harmful]
     * (https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful)
     * (talk by stephan t. lavavej)
     * 
     *
     * Notes:
     * - In C++, `static` function variables are created and initialized once,
     *   when the function is first called, and they remain until the program
     *   is terminated: 
     *   [Static variables in class methods]
     *   (http://stackoverflow.com/questions/6223355/static-variables-in-class-methods)
     * - `std::mt19937` objects are expensive to create.
     *   `std::uniform_int_distribution` objects are said to be pretty cheap.
     */
    unsigned int mtrand(unsigned int low, unsigned int high) {
        static std::random_device rd;
        static std::mt19937 mt(rd());  // engine (mersenne twister)

        return std::uniform_int_distribution<unsigned int>(low, high)(mt);
    }

}

// ----------------------------------------------------------------------------
Neighborhood::Neighborhood(unsigned int size_x, unsigned int size_y)
	:size_x(size_x), size_y(size_y)
{

	{

		// initialize `neighborhood_` and fill with "empty" `Shape`s
		neighborhood_ = new Shape[size_x * size_y]();

		// fill with non-empty shapes so that the ratio of non-empty to empty
		// shapes is `RATIO_FILLED` (from `constants.h`)
		for (int filled = 0; filled < size_x*size_y*RATIO_FILLED; ) {
			unsigned int x = mtrand(0, size_x - 1);
			unsigned int y = mtrand(0, size_y - 1);

			if (this->get(x, y).getType() == "empty") {
				this->set(x, y, mtrand(0, 1) ? Shape("triangle")
					: Shape("square"));
				filled++;
			}
		}
	}
}


Neighborhood::~Neighborhood()
{
	delete[] neighborhood_;
}



Shape Neighborhood::get(unsigned int x, unsigned int y) const
{
	return neighborhood_[y * size_x + x];
}
/**
* Return the `Shape` at `neighborhood_[ y * size_x + x ]`.
*
* If `x` or `y` is out of bounds, should write
* ```
* "ERROR: `Neighborhood::get`: index out of bounds\n"
* ```
* to `cerr` and `exit(1)`.
*/

void Neighborhood::set(unsigned int x, unsigned int y, const Shape & s)
{

	neighborhood_[y*size_x + x] = s;
}
/**
* Set the `Shape` at `neighborhood_[ y * size_x + x ]` to `s`.
*
* If `x` or `y` is out of bounds, should write
* ```
* "ERROR: `Neighborhood::set`: index out of bounds\n"
* ```
* to `cerr` and `exit(1)`.
*/


void Neighborhood::move(unsigned int old_x, unsigned int old_y)
{
	{
		for (;;) {
			unsigned int x = mtrand(0, size_x - 1);
			unsigned int y = mtrand(0, size_y - 1);

			if (get(x, y).getType() == "empty") {
				set(x, y, get(old_x, old_y));
				set(old_x, old_y, Shape("empty"));

				break;
			}
		}
	}
}


void Neighborhood::animate(unsigned int frames)
{


	unsigned int size_x = TERM_SIZE_X / Shape::size_x;
	unsigned int size_y = TERM_SIZE_Y / Shape::size_y;
	Neighborhood(size_x, size_y).animate(1000);
}
