import { getUid, setStyle, handleOnClick } from '../config'

const bridge = globalThis.SJSJSBridge;
const NativeView = bridge.NativeRender.NativeComponents.Button

function setButtonProps(comp, newProps, oldProps) {
    const setter = {
        set style(styleSheet) {
            setStyle(comp, styleSheet);
        },
        set text(str) {
            if (str !== oldProps.text) {
                comp.setText(str);
            }
        },
        set onClick (fn) {
            handleOnClick(comp, fn);
        }
    }
    Object.assign(setter, newProps);
}
  
export class ButtonComp extends NativeView {
    constructor (props) {
        const uid = getUid()
        super({ uid })
        this.uid = uid
        // 必须设置了 min-max 之后才能设置 button 的宽高
        super.setMinimumSize(0, 0)
        super.setMaximumSize(1000000, 1000000)
    }
    setProps(newProps, oldProps) {
        setButtonProps(this, newProps, oldProps);
    }
    insertBefore(child, beforeChild) {
    }
    static tagName = "button";
    appendInitialChild(child) {
    }
    appendChild(child) {
    }
    removeChild(child) {
    }
}