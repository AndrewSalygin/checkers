#ifndef CONSTANTS_H
#define CONSTANTS_H
// Даём имена ASCII строкам
// Рисуем доску из этих элементов
const std::string LEFT_TOP_CORNER 		 = "\u256D"; 
const std::string RIGHT_TOP_CORNER 	   	 = "\u2500\u2500\u2500\u256E\n";
const std::string TOP_LINE		    	 = "\u2500\u2500\u2500\u252C";
const std::string VERTICAL_LINE	   		 = "\u2502";
const std::string BEGIN_BOTTOM_CELL_LINE = "\u251C";
const std::string LEFT_BOTTOM_CORNER 	 = "\u2570";
const std::string BOTTOM_LINE 			 = "\u2500\u2500\u2500\u2534";
const std::string RIGHT_BOTTOM_CORNER 	 = "\u2500\u2500\u2500\u256F";
const std::string END_BOTTOM_CELL_LINE 	 = "\u2500\u2500\u2500\u2524\n";
const std::string INTERCELLULAR_LINE 	 = "\u2500\u2500\u2500\u253C";
const int MAX_LINES 					 = 8;
#endif