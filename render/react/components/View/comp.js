import { getUid, setStyle, handleOnClick } from '../config'
import { unRegistEvent } from '../../core/event'

const bridge = globalThis.SJSJSBridge;
const NativeView = bridge.NativeRender.NativeComponents.View
const NativeFlexLayout = bridge.NativeRender.NativeComponents.FlexLayout

function setViewProps(comp, newProps, oldProps) {
    const setter = {
        set style(styleSheet) {
            setStyle(comp, styleSheet);
        },
        set onClick (fn) {
            handleOnClick(comp, fn);
        }
    }
    Object.assign(setter, newProps);
}
  
export class ViewComp extends NativeView {
    constructor (props) {
        const uid = getUid()
        super({ uid })
        this.uid = uid
    }
    setProps(newProps, oldProps) {
        setViewProps(this, newProps, oldProps);
    }
    insertBefore(child, beforeChild) {
        this.insertChildBefore(child, beforeChild)
    }
    static tagName = "view";
    appendInitialChild(child) {
        this.appendChild(child);
    }
    appendChild(child) {
        // if (!this.layout) {
        //     const flexLayout = new NativeFlexLayout();
        //     this.setLayout(flexLayout);
        //     this.layout = flexLayout;
        // }
        // this.layout.appendChild(child);
        super.appendChild(child)
    }
    removeChild(child) {
        super.removeChild(child);
        child.close();
    }
    unMount () {
        unRegistEvent(this.uid)
    }
}