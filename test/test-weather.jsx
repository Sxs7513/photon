const path = require('path')

const { useState, useEffect, useReducer } = React

const App = () => {
    useEffect(() => {
        console.log(process.platform)
    }, [])

    return (
        <container
            maxSize={{ width: 500, height: 700 }}
            minSize={{ width: 400, height: 600 }}
        >
            <view style={style.wrapper}>
                <image scaledContent={true} src="/assets/images/sky.jpg" style={style.image} />
            </view>
        </container>
    )
}

const style = StyleSheet.create({
    wrapper: {
        'width': '100%',
        'height': '100%',
        'background-color': '#4B4B4B'
    },
    image: {
        'width': '100%',
        'height': '100%',
    }
})

Renderer.render(<App />);