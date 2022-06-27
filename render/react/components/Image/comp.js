import { getUid, setStyle } from '../config'
import { isValidUrl } from '../../utils/helpers';

const bridge = globalThis.SJSJSBridge;
const NativeImage = bridge.NativeRender.NativeComponents.Image

async function getImageBinary(url) {
    const resp = await fetch(url, {
        headers: {
            "Content-Type": "application/octet-stream"
        }
    });
    const imageBuffer = await resp.arrayBuffer();
    return imageBuffer;
}

function setImageProps(comp, newProps, oldProps) {
    const setter = {
        set style(styleSheet) {
            setStyle(comp, styleSheet);
        },
        set children(text) {
            text = Array.isArray(text) ? text.join('') : text;
            comp.setText(text);
        },
        set src(url) {
            if (url && url !== oldProps.url) {
                if (!isValidUrl(url)) {
                    comp.setImage(url)
                } else {
                    getImageBinary(url)
                        .then((buffer) => comp.setImageBinary(buffer))
                        .catch(console.warn);
                }
            }
        },
        set scaledContent (payload) {
            if (typeof payload === 'boolean' && payload !== oldProps.scaledContent) {
                comp.setScaleContent(payload)
            }
        }
    }
    Object.assign(setter, newProps);
}
  
export class ImageComp extends NativeImage {
    constructor (props) {
        const uid = getUid()
        super({ uid })
        this.uid = uid
    }
    setProps(newProps, oldProps) {
        setImageProps(this, newProps, oldProps);
    }
    insertBefore(child, beforeChild) {
    }
    static tagName = "image";
    appendInitialChild(child) {
    }
    appendChild(child) {
        
    }
    removeChild(child) {
        
    }
}