import { dateFormatter } from "../utils/helpers";

export const PlaceDate = props => {
    return (
      <view style={style.containerStyle}>
        <text style={style.placeStyle}>{props.place}</text>
        <text style={style.dateStyle}>{dateFormatter(props.date)}</text>
      </view>
    );
};

const style = StyleSheet.create({
    placeStyle: {
        "font-size": "20px", 
        "color": "white"
    },
    dateStyle: {
        "font-size": "12px",
        "color": "white",
    },
    containerStyle: {
        "display": "flex",
        "flex": 1,
        "flex-shrink": 0,
        'flex-direction': 'column',
        'justify-content': 'center',
        'align-items': 'center',
    }
})