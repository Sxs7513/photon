export const Summary = props => {
    return (
      <view style={style.containerStyle}>
        <text style={style.textStyle}>{`<b>${props.title}</b>: <i>${
          props.description
        }</i>.`}</text>
      </view>
    );
};

const style = StyleSheet.create({
    containerStyle: {
        "align-items": "center",
        "justify-content": "center",
        "height": "50px",
        "flex-shrink": 0,
        "flex-grow": 0,
    },
    textStyle: {
        "text-align": "center",
        "color": "white",
        "height": "30px",
    }
})