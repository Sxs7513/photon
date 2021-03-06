import { ScrollViewComp } from './comp'

export default class ScrollView {
    tagName = 'scrollview';
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
        const instance = new ScrollViewComp();
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
        instance.resetChild();
    }
    commitUnmount (instance) {
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
