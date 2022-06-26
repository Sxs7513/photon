import { View, Container } from 'photon-ui'
import { useReducer } from 'react'
import SearchBar from './components/searchbar'
import List from './components/list'

const minSize = { width: 500, height: 520 };

const initialState = {
    list: []
}

const reducer = (state, action) => {
    const newState = { ...state };
    switch (action.type) {
        case "list": {
            newState.list = action.value
        }
    }
    return newState
}

function App () {
    const [state, dispatch] = useReducer(reducer, initialState);

    return  (
        <Container 
            minSize={minSize}
            title="Meme Search"
            style={style.wrapper}
        >
            <SearchBar 
                onChange={(data) => dispatch({ type: 'list', value: data })}
            />
            <List data={state.list} />
        </Container>
    );
}

const style = StyleSheet.create({
    wrapper: {
        'background-color': '#323234'
    }
})

Renderer.render(<App />);
