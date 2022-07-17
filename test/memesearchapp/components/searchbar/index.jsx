import { View, Image, Input, Button } from 'photon-ui'
import { useCallback, useEffect, useRef, useState } from 'react'

const GIPHY_API_KEY = 'CwOJl2PRaXe9fnV2xHxRoCbP8gOM3erY'

export default function SearchBar ({ onChange }) {
    const input = useRef(null);
    const [isFocus, setFocus] = useState(false)

    const search = useCallback(async (searchTerm) => {
        try {
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

            xh.showLoading()
            const res = await fetch(url, {
                headers: {
                    "Content-type": "application/x-www-form-urlencoded; charset=UTF-8",
                },
            });
            const data = await res.json();
            onChange(data.data || [])
        } finally {
            xh.hideLoading()
        }
    }, [])

    return (
        <View style={style.wrapper}>
            <Input 
                ref={input} 
                style={[style.input, (isFocus ? style.focus : null)]} 
                onChange={e => {}} 
                onFocus={() => { setFocus(true) }}
                onBlur={() => { setFocus(false) }}
            />
            <Button onClick={() => search(input.current.text)} style={style.button} text={' 🔎 '} />
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
    },
    focus: {
        'border': '4px solid #4b6cd5',
    }
})