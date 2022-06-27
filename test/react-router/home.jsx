
import { useNavigate } from "react-router";
const { useCallback } = React

export default function Home() {
    const history = useNavigate();

    const goToCalculator = useCallback(() => {
        history('/calculator')
    }, [])

    const goToWeather = useCallback(() => {
        history('/weather')
    }, [])

    return (
        <view
            style={style.wrapper}
        >
            <button onClick={goToCalculator} text="Go to Calculator 🤓"></button>
            <button onClick={goToWeather} text="Go to Weather 🤓"></button>
        </view>
    );
}

const style = StyleSheet.create({
    wrapper: {
        'height': '100%',
        'align-items': 'center',
        'justify-content': 'center'
    }
})