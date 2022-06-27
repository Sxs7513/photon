
const { useState, useEffect, useReducer } = React

const initialState = {
  display: "",
  total: 0,
  pendingOp: "~",
  valueBuffer: ""
};

const reducer = (state, action) => {
  const newState = { ...state };
  switch (action.type) {
    case "operation": {
      switch (newState.pendingOp) {
        case "+": {
          newState.total =
            newState.total + parseFloat(state.valueBuffer || "0");
          break;
        }
        case "-": {
          newState.total =
            newState.total - parseFloat(state.valueBuffer || "0");
          break;
        }
        case "*": {
          newState.total =
            newState.total * parseFloat(state.valueBuffer || "0");
          break;
        }
        case "/": {
          newState.total =
            newState.total / parseFloat(state.valueBuffer || "1");
          break;
        }
        case "=": {
          break;
        }
        case "~": {
          newState.total = parseFloat(state.valueBuffer || "0");
        }
        default:
      }
      newState.valueBuffer = "";
      newState.display = action.value;
      if (action.value === "=") {
        const total = newState.total;
        Object.assign(newState, initialState);
        newState.total = total;
        newState.display = `${total}`;
      }
      if (action.value === "~") {
        Object.assign(newState, initialState);
      }
      newState.pendingOp = `${action.value}`;
      break;
    }
    case "value": {
      if (state.pendingOp === "=") {
        newState.pendingOp = "~";
      }
      if (!state.valueBuffer) {
        newState.display = action.value;
        newState.valueBuffer = `${action.value}`;
      } else {
        newState.display = `${state.display}` + `${action.value}`;
        newState.valueBuffer += `${action.value}`;
      }
      break;
    }
    default:
      throw new Error("Invalid operation");
  }
  return newState;
};

const App = () => {
  const [state, dispatch] = useReducer(reducer, initialState);
  const onOperator = (value) => {
    dispatch({ type: "operation", value });
  };
  const onValue = (value) => {
    dispatch({ type: "value", value });
  };
  const onKeyRelease = (evt) => {
    const operatorKeys = ["~", "/", "*", "-", "=", "+"];
    const valueKeys = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "."];
    const keyEvt = new QKeyEvent(evt);
    const keyText = keyEvt.text();
    if (operatorKeys.includes(keyText)) {
      dispatch({ type: "operation", value: keyText });
    } else if (valueKeys.includes(keyText)) {
      dispatch({ type: "value", value: keyText });
    }
  };

  useEffect(() => {
    // setTimeout(async () => {
    //   await xh.showLoading()

    //   console.log('hideLoading')
    // }, 1000)
    xh.showLoading({ dutation: 8000 })
    const url = 'https://httpbin.org/post';
    const data = JSON.stringify({ foo: 'bar', bar: 'baz' });
    const xhr = new XMLHttpRequest();
    xhr.open('POST', url);
    xhr.setRequestHeader('Content-Type', 'application/json');
    xhr.onloadend = () => {
      xh.hideLoading()
      console.log('status is: ', xhr.status)
      console.log('response is: ', xhr.response)
    };
    xhr.send(data);
  }, [])

  return (
    <container
      maxSize={{ width: 500, height: 700 }}
      minSize={{ width: 400, height: 600 }}
    >
      <view style={style.wrapper}>
        <view style={[style.row, style.row1]}>
          <button
            text="AC"
            style={[style.acbtn]}
            onClick={(e) => { onOperator("~") }}
          />
          <view style={style.resultWrapper}>
            <text style={style.result}>{state.display || "0"}</text>
          </view>
        </view>
        <view style={[style.row, style.row2]}>
          <button
            style={[style.btn]}
            text="7"
            onClick={(e) => { onValue("7") }}
          />
          <button
            style={[style.btn]}
            text="8"
            onClick={(e) => { onValue("8") }}
          />
          <button
            style={[style.btn]}
            text="9"
            onClick={(e) => { onValue("9") }}
          />
          <button
            style={[style.btn, style.opBtnY]}
            text="/"
            onClick={(e) => { onOperator("/") }}
          />
        </view>
        <view style={[style.row]}>
          <button
            style={[style.btn]}
            text="4"
            onClick={(e) => { onValue("4") }}
          />
          <button
            style={[style.btn]}
            text="5"
            onClick={(e) => { onValue("5") }}
          />
          <button
            style={[style.btn]}
            text="6"
            onClick={(e) => { onValue("6") }}
          />
          <button
            style={[style.btn, style.opBtnY]}
            text="x"
            onClick={(e) => { onOperator("*") }}
          />
        </view>
        <view style={[style.row]}>
          <button
            style={[style.btn]}
            text="1"
            onClick={(e) => { onValue("1") }}
          />
          <button
            style={[style.btn]}
            text="2"
            onClick={(e) => { onValue("2") }}
          />
          <button
            style={[style.btn]}
            text="3"
            onClick={(e) => { onValue("3") }}
          />
          <button
            style={[style.btn, style.opBtnY]}
            text="-"
            onClick={(e) => { onOperator("-") }}
          />
        </view>
        <view style={[style.row]}>
          <button
            style={[style.btn]}
            text="0"
            onClick={(e) => { onValue("0") }}
          />
          <button
            style={[style.btn]}
            text="."
            onClick={(e) => { onValue(".") }}
          />
          <button
            style={[style.btn]}
            text="="
            onClick={(e) => { onOperator("=") }}
          />
          <button
            style={[style.btn, style.opBtnY]}
            text="+"
            onClick={(e) => { onOperator("+") }}
          />
        </view>
      </view>
    </container>
  );
};

const style = StyleSheet.create({
  wrapper: {
    'flex': 1,
    'flex-direction': 'column',
  },
  row: {
    'flex': 1,
    'align-items': 'stretch',
    'justify-content': 'space-between',
    'flex-direction': 'row',
    'background-color': '#4B4B4B'
  },
  row1: {
    'background-color': '#1E1E1E'
  },
  row2: {
    'background-color': '#2E2E2E'
  },
  btn: {
    'border': '1px solid red',
    'font-size': '20px',
    'color': 'white',
    'min-width': '25%'
  },
  opBtnY: {
    'background-color': '#FD8D0E'
  },
  acbtn: {
    'border': '1px solid red',
    'font-size': '20px',
    'color': 'white',
    'min-width': '25%',
    'flex-grow': 0,
  },
  resultWrapper: {
    'flex': 1,
    'flex-direction': 'row',
    'align-items': 'center',
    'justify-content': 'flex-end',
  },
  result: {
    'text-align': 'right',
    'padding-horizontal': '5px',
    'font-size': '40px',
    'color': 'white',
  },
})

Renderer.render(<App />);
