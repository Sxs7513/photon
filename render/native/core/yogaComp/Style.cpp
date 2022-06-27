#include "Style.h"

std::unordered_map<std::string, int> YogaStyle::NodeAlign{
    {"auto", YGAlignAuto},
    {"flex-start", YGAlignFlexStart},
    {"center", YGAlignCenter},
    {"flex-end", YGAlignFlexEnd},
    {"stretch", YGAlignStretch},
    {"baseline", YGAlignBaseline},
    {"space-between", YGAlignSpaceBetween},
    {"space-around", YGAlignSpaceAround},
};

std::unordered_map<std::string, int> YogaStyle::NodeJustifyContent{
    {"flex-start", YGJustifyFlexStart},
    {"center", YGJustifyCenter},
    {"flex-end", YGJustifyFlexEnd},
    {"space-between", YGJustifySpaceBetween},
    {"space-around", YGJustifySpaceAround},
    {"space-evenly", YGJustifySpaceEvenly}};

std::unordered_map<std::string, int> YogaStyle::NodeDirection{
    {"inherit", YGDirectionInherit},
    {"ltr", YGDirectionLTR},
    {"rtl", YGDirectionRTL}};

std::unordered_map<std::string, int> YogaStyle::NodeDisplay{
    {"flex", YGDisplayFlex}, {"none", YGDisplayNone}};

std::unordered_map<std::string, int> YogaStyle::NodeFlexDirection{
    {"column", YGFlexDirectionColumn},
    {"column-reverse", YGFlexDirectionColumnReverse},
    {"row", YGFlexDirectionRow},
    {"row-reverse", YGFlexDirectionRowReverse}};

std::unordered_map<std::string, int> YogaStyle::NodeOverflow{
    {"visible", YGOverflowVisible},
    {"hidden", YGOverflowHidden},
    {"scroll", YGOverflowScroll}};

std::unordered_map<std::string, int> YogaStyle::NodePosition{
    {"relative", YGPositionTypeRelative},
    {"absolute", YGPositionTypeAbsolute},
};

std::unordered_map<std::string, int> YogaStyle::NodeWrap{
    {"no-wrap", YGWrapNoWrap},
    {"wrap", YGWrapWrap},
    {"wrap-reverse", YGWrapWrapReverse}};

NodeValueUnit YogaStyle::parseMeasurement(QString rawValue) {
  float value = std::stof(rawValue.toStdString());
  if (rawValue.back() == "%") {
    return NodeValueUnit(value, YGUnitPercent);
  }
  return NodeValueUnit(value, YGUnitPoint);
}
