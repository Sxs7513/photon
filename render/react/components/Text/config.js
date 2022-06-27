import { TextComp } from './comp'

export default class TextConfig {
    tagName = 'text';
    native = null;
    shouldSetTextContent() {
        return true;
    }
    createInstance(
        newProps,
        rootInstance,
        context,
        workInProgress
    ) {
        const instance = new TextComp();
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
