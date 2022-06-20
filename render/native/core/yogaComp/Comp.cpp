#include "Comp.h"
#include "Style.h"

#include <QDebug>
#include "deps/yoga/Yoga.h"

void YogaComp::setYDisplay(QString rawValue) {
  try {
    std::string rawDisplay = rawValue.toStdString();
    int value = YogaStyle::NodeDisplay.at(rawDisplay);
    YGNodeStyleSetDisplay(this->getFlexNode(), static_cast<YGDisplay>(value));
    this->_yDisplay = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: display: " << rawValue;
  }
}
void YogaComp::setYAlignItems(QString rawValue) {
  try {
    std::string rawAlignItems = rawValue.toStdString();
    int value = YogaStyle::NodeAlign.at(rawAlignItems);
    YGNodeStyleSetAlignItems(this->getFlexNode(), static_cast<YGAlign>(value));
    this->_yAlignItems = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: alignItems: " << rawValue;
  }
}
void YogaComp::setYAlignContent(QString rawValue) {
  try {
    std::string rawAlignContent = rawValue.toStdString();
    int value = YogaStyle::NodeAlign.at(rawAlignContent);
    YGNodeStyleSetAlignContent(this->getFlexNode(),
                               static_cast<YGAlign>(value));
    this->_yAlignContent = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: alignContent: " << rawValue;
  }
}
void YogaComp::setYAlignSelf(QString rawValue) {
  try {
    std::string rawAlignSelf = rawValue.toStdString();
    int value = YogaStyle::NodeAlign.at(rawAlignSelf);
    YGNodeStyleSetAlignSelf(this->getFlexNode(), static_cast<YGAlign>(value));
    this->_yAlignSelf = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: alignSelf: " << rawValue;
  }
}
void YogaComp::setYJustifyContent(QString rawValue) {
  try {
    std::string rawJustifyContent = rawValue.toStdString();
    int value = YogaStyle::NodeJustifyContent.at(rawJustifyContent);
    YGNodeStyleSetJustifyContent(this->getFlexNode(),
                                 static_cast<YGJustify>(value));
    this->_yJustifyContent = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: justifyContent: " << rawValue;
  }
}
void YogaComp::setYDirection(QString rawValue) {
  try {
    std::string rawDirection = rawValue.toStdString();
    int value = YogaStyle::NodeDirection.at(rawDirection);
    YGNodeStyleSetDirection(this->getFlexNode(),
                            static_cast<YGDirection>(value));
    this->_yDirection = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: direction: " << rawValue;
  }
}
void YogaComp::setYFlexDirection(QString rawValue) {
  try {
    std::string rawFlexDirection = rawValue.toStdString();
    int value = YogaStyle::NodeFlexDirection.at(rawFlexDirection);
    YGNodeStyleSetFlexDirection(this->getFlexNode(),
                                static_cast<YGFlexDirection>(value));
    this->_yFlexDirection = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: flexDirection: " << rawValue;
  }
}
void YogaComp::setYOverflow(QString rawValue) {
  try {
    std::string rawOverflow = rawValue.toStdString();
    int value = YogaStyle::NodeOverflow.at(rawOverflow);
    YGNodeStyleSetOverflow(this->getFlexNode(), static_cast<YGOverflow>(value));
    this->_yOverflow = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: overflow: " << rawValue;
  }
}
void YogaComp::setYPosition(QString rawValue) {
  try {
    std::string rawPosition = rawValue.toStdString();
    int value = YogaStyle::NodePosition.at(rawPosition);
    YGNodeStyleSetPositionType(this->getFlexNode(),
                               static_cast<YGPositionType>(value));
    this->_yPosition = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: positionType: " << rawValue;
  }
}
void YogaComp::setYFlexWrap(QString rawValue) {
  try {
    std::string rawFlexWrap = rawValue.toStdString();
    int value = YogaStyle::NodeWrap.at(rawFlexWrap);
    YGNodeStyleSetFlexWrap(this->getFlexNode(), static_cast<YGWrap>(value));
    this->_yFlexWrap = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: flexWrap: " << rawValue;
  }
}
void YogaComp::setYFlex(float rawValue) {
  try {
    YGNodeStyleSetFlex(this->getFlexNode(), rawValue);
    this->_yFlex = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: flex: " << rawValue;
  }
}
void YogaComp::setYFlexGrow(float rawValue) {
  try {
    YGNodeStyleSetFlexGrow(this->getFlexNode(), rawValue);
    this->_yFlexGrow = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: flexGrow: " << rawValue;
  }
}
void YogaComp::setYFlexShrink(float rawValue) {
  try {
    YGNodeStyleSetFlexShrink(this->getFlexNode(), rawValue);
    this->_yFlexShrink = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: flexShrink: " << rawValue;
  }
}
void YogaComp::setYAspectRatio(float rawValue) {
  try {
    YGNodeStyleSetAspectRatio(this->getFlexNode(), rawValue);
    this->_yAspectRatio = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: aspectRatio: " << rawValue;
  }
}
void YogaComp::setYNodeTop(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetPositionPercent(this->getFlexNode(), YGEdgeTop,
                                        measurement.value)
        : YGNodeStyleSetPosition(this->getFlexNode(), YGEdgeTop,
                                 measurement.value);
    this->_yTop = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: top: " << rawValue;
  }
}
void YogaComp::setYNodeRight(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetPositionPercent(this->getFlexNode(), YGEdgeRight,
                                        measurement.value)
        : YGNodeStyleSetPosition(this->getFlexNode(), YGEdgeRight,
                                 measurement.value);
    this->_yRight = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: right: " << rawValue;
  }
}

void YogaComp::setYNodeBottom(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetPositionPercent(this->getFlexNode(), YGEdgeBottom,
                                        measurement.value)
        : YGNodeStyleSetPosition(this->getFlexNode(), YGEdgeBottom,
                                 measurement.value);
    this->_yBottom = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: bottom: " << rawValue;
  }
}

void YogaComp::setYNodeLeft(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetPositionPercent(this->getFlexNode(), YGEdgeLeft,
                                        measurement.value)
        : YGNodeStyleSetPosition(this->getFlexNode(), YGEdgeLeft,
                                 measurement.value);
    this->_yLeft = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: left: " << rawValue;
  }
}

void YogaComp::setYFlexBasis(QString rawValue) {
  try {
    if (rawValue == "auto") {
      YGNodeStyleSetFlexBasisAuto(this->getFlexNode());
    } else {
      NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
      (measurement.unit == YGUnitPercent)
          ? YGNodeStyleSetFlexBasisPercent(this->getFlexNode(),
                                           measurement.value)
          : YGNodeStyleSetFlexBasis(this->getFlexNode(), measurement.value);
    }
    this->_yFlexBasis = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: flexBasis: " << rawValue;
  }
}

void YogaComp::setYMinWidth(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetMinWidthPercent(this->getFlexNode(), measurement.value)
        : YGNodeStyleSetMinWidth(this->getFlexNode(), measurement.value);
    this->_yMinWidth = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: minWidth: " << rawValue;
  }
}
void YogaComp::setYMinHeight(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetMinHeightPercent(this->getFlexNode(), measurement.value)
        : YGNodeStyleSetMinHeight(this->getFlexNode(), measurement.value);
    this->_yMinHeight = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: minHeight: " << rawValue;
  }
}
void YogaComp::setYWidth(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetWidthPercent(this->getFlexNode(), measurement.value)
        : YGNodeStyleSetWidth(this->getFlexNode(), measurement.value);
    this->_yWidth = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: yWidth: " << rawValue;
  }
}
void YogaComp::setYHeight(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetHeightPercent(this->getFlexNode(), measurement.value)
        : YGNodeStyleSetHeight(this->getFlexNode(), measurement.value);
    this->_yHeight = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: yHeight: " << rawValue;
  }
}
void YogaComp::setYMaxWidth(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetMaxWidthPercent(this->getFlexNode(), measurement.value)
        : YGNodeStyleSetMaxWidth(this->getFlexNode(), measurement.value);
    this->_yMaxWidth = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: maxWidth: " << rawValue;
  }
}
void YogaComp::setYMaxHeight(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetMaxHeightPercent(this->getFlexNode(), measurement.value)
        : YGNodeStyleSetMaxHeight(this->getFlexNode(), measurement.value);
    this->_yMaxHeight = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: maxHeight: " << rawValue;
  }
}
void YogaComp::setYPaddingTop(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetPaddingPercent(this->getFlexNode(), YGEdgeTop,
                                       measurement.value)
        : YGNodeStyleSetPadding(this->getFlexNode(), YGEdgeTop,
                                measurement.value);
    this->_yPaddingTop = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: paddingTop: " << rawValue;
  }
}
void YogaComp::setYPaddingRight(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetPaddingPercent(this->getFlexNode(), YGEdgeRight,
                                       measurement.value)
        : YGNodeStyleSetPadding(this->getFlexNode(), YGEdgeRight,
                                measurement.value);
    this->_yPaddingRight = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: paddingRight: " << rawValue;
  }
}
void YogaComp::setYPaddingBottom(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetPaddingPercent(this->getFlexNode(), YGEdgeBottom,
                                       measurement.value)
        : YGNodeStyleSetPadding(this->getFlexNode(), YGEdgeBottom,
                                measurement.value);
    this->_yPaddingBottom = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: paddingBottom: " << rawValue;
  }
}
void YogaComp::setYPaddingLeft(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetPaddingPercent(this->getFlexNode(), YGEdgeLeft,
                                       measurement.value)
        : YGNodeStyleSetPadding(this->getFlexNode(), YGEdgeLeft,
                                measurement.value);
    this->_yPaddingLeft = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: paddingLeft: " << rawValue;
  }
}
void YogaComp::setYPaddingHorizontal(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetPaddingPercent(this->getFlexNode(), YGEdgeHorizontal,
                                       measurement.value)
        : YGNodeStyleSetPadding(this->getFlexNode(), YGEdgeHorizontal,
                                measurement.value);
    this->_yPaddingHorizontal = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: paddingHorizontal: " << rawValue;
  }
}
void YogaComp::setYPaddingVertical(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetPaddingPercent(this->getFlexNode(), YGEdgeVertical,
                                       measurement.value)
        : YGNodeStyleSetPadding(this->getFlexNode(), YGEdgeVertical,
                                measurement.value);
    this->_yPaddingVertical = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: paddingVertical: " << rawValue;
  }
}
void YogaComp::setYPadding(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetPaddingPercent(this->getFlexNode(), YGEdgeAll,
                                       measurement.value)
        : YGNodeStyleSetPadding(this->getFlexNode(), YGEdgeAll,
                                measurement.value);
    this->_yPadding = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: padding: " << rawValue;
  }
}
void YogaComp::setYMarginTop(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetMarginPercent(this->getFlexNode(), YGEdgeTop,
                                      measurement.value)
        : YGNodeStyleSetMargin(this->getFlexNode(), YGEdgeTop,
                               measurement.value);
    this->_yMarginTop = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: marginTop: " << rawValue;
  }
}
void YogaComp::setYMarginRight(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetMarginPercent(this->getFlexNode(), YGEdgeRight,
                                      measurement.value)
        : YGNodeStyleSetMargin(this->getFlexNode(), YGEdgeRight,
                               measurement.value);
    this->_yMarginRight = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: marginRight: " << rawValue;
  }
}
void YogaComp::setYMarginBottom(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetMarginPercent(this->getFlexNode(), YGEdgeBottom,
                                      measurement.value)
        : YGNodeStyleSetMargin(this->getFlexNode(), YGEdgeBottom,
                               measurement.value);
    this->_yMarginBottom = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: marginBottom: " << rawValue;
  }
}
void YogaComp::setYMarginLeft(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetMarginPercent(this->getFlexNode(), YGEdgeLeft,
                                      measurement.value)
        : YGNodeStyleSetMargin(this->getFlexNode(), YGEdgeLeft,
                               measurement.value);
    this->_yMarginLeft = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: marginLeft: " << rawValue;
  }
}
void YogaComp::setYMarginHorizontal(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetMarginPercent(this->getFlexNode(), YGEdgeHorizontal,
                                      measurement.value)
        : YGNodeStyleSetMargin(this->getFlexNode(), YGEdgeHorizontal,
                               measurement.value);
    this->_yMarginHorizontal = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: marginHorizontal: " << rawValue;
  }
}
void YogaComp::setYMarginVertical(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetMarginPercent(this->getFlexNode(), YGEdgeVertical,
                                      measurement.value)
        : YGNodeStyleSetMargin(this->getFlexNode(), YGEdgeVertical,
                               measurement.value);
    this->_yMarginVertical = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: marginVertical: " << rawValue;
  }
}
void YogaComp::setYMarginAll(QString rawValue) {
  try {
    NodeValueUnit measurement = YogaStyle::parseMeasurement(rawValue);
    (measurement.unit == YGUnitPercent)
        ? YGNodeStyleSetMarginPercent(this->getFlexNode(), YGEdgeAll,
                                      measurement.value)
        : YGNodeStyleSetMargin(this->getFlexNode(), YGEdgeAll,
                               measurement.value);
    this->_yMargin = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: margin: " << rawValue;
  }
}

void YogaComp::setYBorderTop(float rawValue) {
  try {
    YGNodeStyleSetBorder(this->getFlexNode(), YGEdgeTop, rawValue);
    this->_yBorderTop = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: borderTop: " << rawValue;
  }
}
void YogaComp::setYBorderRight(float rawValue) {
  try {
    YGNodeStyleSetBorder(this->getFlexNode(), YGEdgeRight, rawValue);
    this->_yBorderRight = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: borderRight: " << rawValue;
  }
}
void YogaComp::setYBorderBottom(float rawValue) {
  try {
    YGNodeStyleSetBorder(this->getFlexNode(), YGEdgeBottom, rawValue);
    this->_yBorderBottom = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: borderBottom: " << rawValue;
  }
}
void YogaComp::setYBorderLeft(float rawValue) {
  try {
    YGNodeStyleSetBorder(this->getFlexNode(), YGEdgeLeft, rawValue);
    this->_yBorderLeft = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: borderLeft: " << rawValue;
  }
}
void YogaComp::setYBorderHorizontal(float rawValue) {
  try {
    YGNodeStyleSetBorder(this->getFlexNode(), YGEdgeHorizontal, rawValue);
    this->_yBorderHorizontal = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: borderHorizontal: " << rawValue;
  }
}
void YogaComp::setYBorderVertical(float rawValue) {
  try {
    YGNodeStyleSetBorder(this->getFlexNode(), YGEdgeVertical, rawValue);
    this->_yBorderVertical = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: borderVertical: " << rawValue;
  }
}

void YogaComp::setYBorder(float rawValue) {
  try {
    YGNodeStyleSetBorder(this->getFlexNode(), YGEdgeAll, rawValue);
    this->_yBorder = rawValue;
  } catch (...) {
    qWarning() << "Invalid value: border: " << rawValue;
  }
}
