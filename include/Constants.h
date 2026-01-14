#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace constants
{
    // Constants
   	inline int gScreenWidth = 640; // Gör skärmen 640 pixlar bred
   	inline int gScreenHeight = 480; // Gör skärmen 480 pixlar hög


   	// PATH TO OUR RESOURCE FOLDER 'resources', 'gResPath'
   	const std::string gResPath { "./resources/" };

	// PATHS TO ALL OUR EXTERNAL RESOURCES using 'gResPath'
	const std::string fontPath { gResPath + "fonts/arial.ttf" };
	const std::string rocketship_str {gResPath + "images/rocketship.png"};  //ger etiketter på bilderna som ska nås
	const std::string rocketship2_str {gResPath + "images/rocketship-2.png"};
	const std::string alien_str {gResPath + "images/enemy.png"}; // fixed typo
	const std::string alien2_str {gResPath + "images/enemy-1.png"}; // added ; in the end each line
	const std::string background_str {gResPath + "images/background-alternativ-1.jpg"}; 
	const std::string background2_str {gResPath + "images/background-alternativ-2.png"};
	const std::string bullet_str {gResPath + "images/bullet.png"};
	 
}


#endif