import { ImageComp } from './comp'

export default class ImageConfig {
    tagName = 'image';
    native = null;
    shouldSetTextContent() {
        return false;
    }
    createInstance(
        newProps,
        rootInstance,
        context,
        workInProgress
    ) {
        const instance = new ImageComp();
        instance.setProps(newProps, {});
        return instance;
    }
    commitMount(
        instance,
        newProps,
        internalInstanceHandle
    ) {
    }
    commitUpdate(
        instance,
        updatePayload,
        oldProps,
        newProps,
        finishedWork
    ) {
        instance.setProps(newProps, oldProps);
    }
    setProps(newProps, oldProps) {
    }
    insertBefore(child, beforeChild) {

    }
    appendInitialChild(child) {
    }
    appendChild(child) {
        
    }
    removeChild(child) {
    }
}
