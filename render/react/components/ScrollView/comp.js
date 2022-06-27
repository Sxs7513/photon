import { getUid, setStyle, handleOnClick } from '../config'
import { unRegistEvent } from '../../core/event'

const bridge = globalThis.SJSJSBridge;
const NativeView = bridge.NativeRender.NativeComponents.ScrollView

function setScrollViewProps(comp, newProps, oldProps) {
    const setter = {
        set style(styleSheet) {
            setStyle(comp, styleSheet);
        },
        set horizontal (payload) {
            if (payload !== oldProps.horizontal) {
                comp.setHorizontalEnable (typeof payload === 'boolean' ? payload : true)
            }
        },
        set vertical (payload) {
            if (payload !== oldProps.vertical) {
                comp.setVerticalEnable (typeof payload === 'boolean' ? payload : true)
            }
        }
    }
    Object.assign(setter, newProps);
}
  
export class ScrollViewComp extends NativeView {
    constructor (props) {
        const uid = getUid()
        super({ uid })
        this.uid = uid
    }
    setProps(newProps, oldProps) {
        setScrollViewProps(this, newProps, oldProps);
    }
    insertBefore(child, beforeChild) {
        this.insertChildBefore(child, beforeChild)
    }
    static tagName = "scrollview";
    appendInitialChild(child) {
        this.appendChild(child);
    }
    appendChild(child) {
        super.appendChild(child);
    }
    removeChild(child) {
        super.removeChild(child);
    }
    unMount () {
        unRegistEvent(this.uid)
    }
}