
export const TemperatureBox = props => {
    return (
      <view style={style.temperatureBoxStyle}>
        <text style={style.currentTempStyle}>{`${props.now} <sup>o</sup>C`}</text>
        <view style={style.smallBox}>
          <text style={style.smallInfo}>{`${props.min} <sup>o</sup>C / ${
            props.max
          } <sup>o</sup>C`}</text>
        </view>
      </view>
    );
};

const style = StyleSheet.create({
    currentTempStyle: {
        "font-size": "20px", 
        "text-align": "center",
        "color": "white"
    },
    temperatureBoxStyle: {
        "border-right": "1px solid white",
        "flex": 1,
        "flex-shrink": 0,
        "flex-grow": 0,
        "align-items": "center",
        "justify-content": "center",
        "flex-direction": "column",
    },
    smallBox: {
        "flex-direction": "row",
        "align-items": "center",
        "justify-content": "center"
    },
    smallInfo: {
        "width": "150px",
        "color": "white",
        "text-align": "center",
    }
})