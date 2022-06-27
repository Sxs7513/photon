import { View, Image, ScrollView, Text } from 'photon-ui'

export default function List ({ data }) {
    const list = data.map(item => {
        const { url, width } = item.images.fixed_width_small
        return {
            url,
            width
        }
    })

    // if (!list.length) return null;
    return (
        <ScrollView style={style.scrollView} horizontal={false} vertical={true}>
            <View style={style.wrapper}>
                {
                    list.map((item, i) => {
                        return <Image style={[style.image, { width: `${item.width}px` }]} src={item.url} />
                        // return <Text key={i} style={style.image}>2222222{i}</Text>
                    })
                }
            </View>
        </ScrollView>
    )
}

const style = StyleSheet.create({
    image: {
        width: "100px",
        height: "100px",
    },
    wrapper: {
        'flex-direction': 'row',
        'flex-wrap': 'wrap',
        'justify-content': 'space-around',
        'width': '500px',
        'height': '100%',
    },
    scrollView: {
        'background-color': '#323234',
        'width': '500px',
        'height': '400px',
    }
})