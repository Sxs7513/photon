import { View, Image, Input, Button } from 'photon-ui'
import { useCallback, useEffect, useRef } from 'react'

const GIPHY_API_KEY = 'CwOJl2PRaXe9fnV2xHxRoCbP8gOM3erY'

export default function SearchBar ({ onChange }) {
    const input = useRef(null);

    const search = useCallback(async (searchTerm) => {
        let url = 'https://api.giphy.com/v1/gifs/search?';
        const obj = {
            api_key: GIPHY_API_KEY,
            limit: 30,
            q: searchTerm,
            lang: 'en',
            offset: 0,
            rating: 'pg-13'
        }
        Object.keys(obj).forEach(key => {
            url += `${key}=${obj[key]}&`
        })
        url = url.substring(0, url.length - 2)
        const res = await fetch(url, {
            headers: {
                "Content-type": "application/x-www-form-urlencoded; charset=UTF-8",
            },
        });
        return res.json();
    }, [])

    useEffect(() => {
        // (async () => {
        //     try {
        //         xh.showLoading()
        //         const resp = await search('hello')
        //         onChange(resp?.data)
        //     } catch (e) {
        //         console.error(e)
        //     } finally {
        //         xh.hideLoading()
        //     }
        // })()
    }, [])

    return (
        <View style={style.wrapper}>
            <Input ref={input} style={style.input} onChange={e => console.log(e)} />
            <Button onClick={() => console.log(input.current.text)} style={style.button} text={' 🔎 '} />
        </View>
    )
}

const style = StyleSheet.create({
    wrapper: {
        'flex-direction': 'row',
        'padding': '10px',
        'align-items': 'center',
        'width': '100%',
    },
    input: {
        'flex': 1,
        'height': '30px',
    },
    button: {
        'margin-left': '5px',
        'width': '50px',
        'height': '30px',
    }
})