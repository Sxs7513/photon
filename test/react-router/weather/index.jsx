import { getCurrentWeather } from "./utils/weather";
import { WeatherIcon } from "./components/WeatherIcon";
import { TemperatureBox } from "./components/TemperatureBox";
import { Summary } from "./components/Summary";
import { PlaceDate } from "./components/PlaceDate";

const path = require('path')

const { useState, useEffect, useCallback } = React

const defaultState = {
    weather: [],
    main: {
      temp: 0,
      temp_min: 0,
      temp_max: 0
    },
    name: "NA"
};

export default () => {
    const [weather, setWeather] = useState(defaultState);

    const getWeather = useCallback(async () => {
        try {
          const data = await getCurrentWeather();
          setWeather(data);
        } catch (err) {
          console.log(err);
        }
      }, []);

    useEffect(() => {
        getWeather();
    }, []);

    const summary = weather.weather[0] || {};
    return (
            <view style={style.wrapper}>
                <image style={style.backgroundImage} src={path.resolve(__dirname, './assets/images/sky.jpg')} scaledContent={true}  />
                <view style={style.iconWrapper}>
                    <WeatherIcon icon={summary.icon} style={style.icon} />
                </view>
                <view style={style.details}>
                    <Summary title={summary.main} description={summary.description} />
                    <view style={style.midBox}>
                        <TemperatureBox
                            now={weather.main.temp}
                            max={weather.main.temp_max}
                            min={weather.main.temp_min}
                        />
                        <PlaceDate place={weather.name} date={new Date()} />
                    </view>
                    <view style={style.buttonBox}>
                        <button text={"Refresh"} style={style.button1} />
                        <button text={"Close"} style={style.button2} />
                    </view>
                </view>
            </view>
    )
}

const style = StyleSheet.create({
    wrapper: {
        'width': '100%',
        'height': '100%',
        'position': 'relative',
        'display': 'flex',
        'flex-direction': 'column',
        'align-items': 'center',
    },
    iconWrapper: {
        "height": "50%",
        'justify-content': 'flex-end',
    },
    icon: {
        "width": "200px",
        "height": "200px",
    },
    backgroundImage: {
        'width': '100%',
        'height': '100%',
        "position": "absolute",
        "left": 0,
        "right": 0,
    },
    midBox: {
        "flex-direction": "row",
        "width": "100%",
        "flex-shrink": 0,
        "flex-grow": 0,
    },
    buttonBox: {
        "height": "30px",
        "margin-top": "20px",
        "flex-direction": "row",
        "justify-content": "center",
        "flex-shrink": 0,
        "flex-grow": 0,
    },
    button1: {
        "margin-right": "10px",
        "width": "80px"
    },
    button2: {
        "width": "80px"
    },
    details: {
        "width": "80%",
        "height": "150px",
        "justify-content": "flex-start",
        'flex-direction': 'column',
        "border-radius": "5px",
        "background-color": "qlineargradient( x1:0 y1:0, x2:0 y2:1, stop:0 rgba(32,65,106,0.6), stop:1 rgba(8,8,8,0.6))"
    }
})