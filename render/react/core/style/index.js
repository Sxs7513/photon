
const rules = {
    display: decl => {
      decl.prop = "qproperty-yDisplay";
      decl.isYogaProp = true
    },
    "align-items": decl => {
      decl.prop = "qproperty-yAlignItems";
      decl.isYogaProp = true
    },
    "align-content": decl => {
      decl.prop = "qproperty-yAlignContent";
      decl.isYogaProp = true
    },
    "align-self": decl => {
      decl.prop = "qproperty-yAlignSelf";
      decl.isYogaProp = true
    },
    "justify-content": decl => {
      decl.prop = "qproperty-yJustifyContent";
      decl.isYogaProp = true
    },
    direction: decl => {
      decl.prop = "qproperty-yDirection";
      decl.isYogaProp = true
    },
    "flex-direction": decl => {
      decl.prop = "qproperty-yFlexDirection";
      decl.isYogaProp = true
    },
    overflow: decl => {
      decl.prop = "qproperty-yOverflow";
      decl.isYogaProp = true
    },
    position: decl => {
      decl.cloneBefore({ prop: "qproperty-yPosition" });
    },
    "flex-wrap": decl => {
      decl.prop = "qproperty-yFlexWrap";
      decl.isYogaProp = true
    },
    flex: decl => {
      decl.prop = "qproperty-yFlex";
      decl.isYogaProp = true
    },
    "flex-grow": decl => {
      decl.prop = "qproperty-yFlexGrow";
      decl.isYogaProp = true
    },
    "flex-shrink": decl => {
      decl.prop = "qproperty-yFlexShrink";
      decl.isYogaProp = true
    },
    "aspect-ratio": decl => {
      decl.prop = "qproperty-yAspectRatio";
      decl.isYogaProp = true
    },
    top: decl => {
      decl.cloneBefore({ prop: "qproperty-yTop" });
    },
    right: decl => {
      decl.cloneBefore({ prop: "qproperty-yRight" });
    },
    bottom: decl => {
      decl.cloneBefore({ prop: "qproperty-yBottom" });
    },
    left: decl => {
      decl.cloneBefore({ prop: "qproperty-yLeft" });
    },
    "flex-basis": decl => {
      decl.prop = "qproperty-yFlexBasis";
      decl.isYogaProp = true
    },
    "min-width": decl => {
      decl.cloneBefore({ prop: "qproperty-yMinWidth" });
    },
    "min-height": decl => {
      decl.cloneBefore({ prop: "qproperty-yMinHeight" });
    },
    width: decl => {
      decl.cloneBefore({ prop: "qproperty-yWidth" });
    },
    height: decl => {
      decl.cloneBefore({ prop: "qproperty-yHeight" });
    },
    "max-width": decl => {
      decl.cloneBefore({ prop: "qproperty-yMaxWidth" });
    },
    "max-height": decl => {
      decl.cloneBefore({ prop: "qproperty-yMaxHeight" });
    },
    "padding-top": decl => {
      decl.cloneBefore({ prop: "qproperty-yPaddingTop" });
    },
    "padding-right": decl => {
      decl.cloneBefore({ prop: "qproperty-yPaddingRight" });
    },
    "padding-bottom": decl => {
      decl.cloneBefore({ prop: "qproperty-yPaddingBottom" });
    },
    "padding-left": decl => {
      decl.cloneBefore({ prop: "qproperty-yPaddingLeft" });
    },
    "padding-horizontal": decl => {
      decl.cloneBefore({ prop: "qproperty-yPaddingHorizontal" });
      decl.cloneBefore({ prop: "padding-right" });
      decl.cloneBefore({ prop: "padding-left" });
      decl.remove();
    },
    "padding-vertical": decl => {
      decl.cloneBefore({ prop: "qproperty-yPaddingVertical" });
      decl.cloneBefore({ prop: "padding-bottom" });
      decl.cloneBefore({ prop: "padding-top" });
      decl.remove();
    },
    padding: decl => {
      decl.cloneBefore({ prop: "qproperty-yPadding" });
    },
    "margin-top": decl => {
      decl.cloneBefore({ prop: "qproperty-yMarginTop" });
    },
    "margin-right": decl => {
      decl.cloneBefore({ prop: "qproperty-yMarginRight" });
    },
    "margin-bottom": decl => {
      decl.cloneBefore({ prop: "qproperty-yMarginBottom" });
    },
    "margin-left": decl => {
      decl.cloneBefore({ prop: "qproperty-yMarginLeft" });
    },
    "margin-horizontal": decl => {
      decl.cloneBefore({ prop: "qproperty-yMarginHorizontal" });
      decl.cloneBefore({ prop: "margin-right" });
      decl.cloneBefore({ prop: "margin-left" });
      decl.remove();
    },
    "margin-vertical": decl => {
      decl.cloneBefore({ prop: "qproperty-yMarginVertical" });
      decl.cloneBefore({ prop: "margin-bottom" });
      decl.cloneBefore({ prop: "margin-top" });
      decl.remove();
    },
    margin: decl => {
      decl.cloneBefore({ prop: "qproperty-yMargin" });
    },
    "border-top": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderTop",
        value: parseInt(`${decl.value}`)
      });
    },
    "border-right": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderRight",
        value: parseInt(`${decl.value}`)
      });
    },
    "border-bottom": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderBottom",
        value: parseInt(`${decl.value}`)
      });
    },
    "border-left": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderLeft",
        value: parseInt(`${decl.value}`)
      });
    },
    "border-horizontal": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderHorizontal",
        value: parseInt(`${decl.value}`)
      });
      decl.cloneBefore({ prop: "border-right" });
      decl.cloneBefore({ prop: "border-left" });
      decl.remove();
    },
    "border-vertical": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderVertical",
        value: parseInt(`${decl.value}`)
      });
      decl.cloneBefore({ prop: "border-bottom" });
      decl.cloneBefore({ prop: "border-top" });
      decl.remove();
    },
    border: decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorder",
        value: parseInt(`${decl.value}`)
      });
    },
    "border-top-width": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderTop",
        value: parseInt(`${decl.value}`)
      });
    },
    "border-right-width": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderRight",
        value: parseInt(`${decl.value}`)
      });
    },
    "border-bottom-width": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderBottom",
        value: parseInt(`${decl.value}`)
      });
    },
    "border-left-width": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderLeft",
        value: parseInt(`${decl.value}`)
      });
    },
    "border-horizontal-width": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderHorizontal",
        value: parseInt(`${decl.value}`)
      });
      decl.cloneBefore({ prop: "border-right" });
      decl.cloneBefore({ prop: "border-left" });
      decl.remove();
    },
    "border-vertical-width": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorderVertical",
        value: parseInt(`${decl.value}`)
      });
      decl.cloneBefore({ prop: "border-bottom" });
      decl.cloneBefore({ prop: "border-top" });
      decl.remove();
    },
    "border-width": decl => {
      decl.cloneBefore({
        prop: "qproperty-yBorder",
        value: parseInt(`${decl.value}`)
      });
    },
    "text-align": decl => {
      decl.prop = 'qproperty-alignment'
      decl.value = `Align${decl.value.replace(/^\S/, s => s.toUpperCase())}`
    }
};

class StyleTransformer {
    constructor ({ prop, value }) {
        this.prop = prop
        this.value = value
        this.removed = false
        this.result = []
    }

    cloneBefore ({ prop, value }) {
        if (!prop) return
        this.result.push({
            prop,
            value: value || this.value
        })
    }

    transform (rule) {
        if (!this.value == void 0) {
          return ''
        }
        if (!rule || typeof rule !== 'function') {
            return `${this.prop}:${this.value};`
        }
        rule.call(this, this)
        if (!this.removed) {
            this.result.unshift({
                prop: this.prop,
                value: this.value
            })
        }

        let str = ''
        this.result.forEach(item => {
          const { value } = item
            str += `${item.prop}: ${(typeof value === 'string' && this.isYogaProp) || value[value.length - 1] === '%' ? `'${value}'` : value };`
        })
        return str
    }

    remove () {
        this.removed = true       
    }
}

class StyleSheet {
    // static transform ({ prop, value }) {
    //     const rule = rules[prop]

    //     return (new StyleTransformer({ prop, value })).transform(rule)
    // }

    // get (obj, prop) {
    //     const styleObj = obj[prop]
    //     const keys = Object.keys(styleObj)
    //     let str = ''
    //     for (prop of keys) {
    //         str += StyleSheet.transform({ prop, value: styleObj[prop] })
    //     }

    //     return str
    // }

    static transform (styleObj) {
      const keys = Object.keys(styleObj)
      let str = ''
      for (let prop of keys) {
          const rule = rules[prop]
          str += (new StyleTransformer({ prop, value: styleObj[prop] })).transform(rule)
      }

      return str
    }

    static create (obj) {
        return obj
        return new Proxy(obj, new StyleSheet)
    }
}

export default StyleSheet