import { loadImageAndGetDataArray, rotateArray } from './helpers';
import { controlColumn, wrapper } from './app.css';
import { LedMatrix } from './components/LedMatrix';
import { Button } from './components/Button';
import { Layout } from './components/Layout';
import { connectionInformation } from './index.css';
import {
  batch,
  Component,
  createMemo,
  createSignal,
  For,
  Show,
} from 'solid-js';
import { useStore } from './store';

export const App: Component = () => {
  const store = useStore();
  const [triggerClear, setTriggerClear] = createSignal(false);

  const rotatedMatrix = createMemo(() =>
    rotateArray(store!.indexMatrix(), store!.rotation())
  );

  const wsMessage = (
    event:
      | 'persist'
      | 'load'
      | 'clear'
      | 'plugin'
      | 'screen'
      | 'led'
      | 'persist-plugin'
      | 'brightness',
    data?: any
  ) =>
    store?.send(
      JSON.stringify({
        event,
        ...data,
      })
    );

  const loadImage = () => {
    loadImageAndGetDataArray((data) => {
      store?.setLeds(() => store?.indexMatrix().map((index) => data[index]));
      wsMessage('screen', { data });
    });
  };

  const clear = () => {
    store?.setLeds([...new Array(256).fill(0)]);
    setTriggerClear(!triggerClear);
    wsMessage('clear');

    store?.toast(`Canvas cleared`, 1000);
  };

  const rotate = (turnRight = false) => {
    let currentRotation = store?.rotation() || 0;

    currentRotation = turnRight
      ? currentRotation > 3
        ? 1
        : currentRotation + 1
      : currentRotation <= 0
      ? 3
      : currentRotation - 1;

    store?.setRotation(currentRotation);

    store?.send(
      JSON.stringify({
        event: 'rotate',
        direction: turnRight ? 'right' : 'left',
      })
    );
  };

  const sendPlugin = (plugin: number) => wsMessage('plugin', { plugin });

  const sendBrightness = (brightness: number) =>
    wsMessage('brightness', { brightness });

  return (
    <Show
      when={store?.connectionState() === 1}
      fallback={
        <Layout
          content={
            <div class={wrapper}>
              <div class={connectionInformation}>
                {store?.connectionStatus}...
              </div>
            </div>
          }
          footer={
            <>
              <a href="#/creator">creator</a>
            </>
          }
        ></Layout>
      }
    >
      <Layout
        content={
          <div class={wrapper}>
            <div>
              <Show when={store?.plugin() === 1}>
                <LedMatrix
                  disabled={store?.plugin() !== 1}
                  data={store?.leds() || []}
                  indexData={rotatedMatrix()}
                  onSetLed={(data) => {
                    wsMessage('led', data);
                  }}
                  onSetMatrix={(data) => {
                    store?.setLeds([...data]);
                  }}
                />
              </Show>
            </div>
          </div>
        }
        footer={
          <>
            <div class={controlColumn}>
              <select
                onInput={(e) => {
                  const currentPlugin = +e.currentTarget.value;
                  sendPlugin(currentPlugin);
                }}
                value={store?.plugin()}
              >
                <For each={store?.plugins()}>
                  {(plugin) => <option value={plugin.id}>{plugin.name}</option>}
                </For>
              </select>

              <Button
                onClick={() => {
                  wsMessage('persist-plugin');
                  store?.toast(`Current mode set as default`, 1500);
                }}
              >
                set as default
              </Button>
            </div>

            <div class={controlColumn}>
              <Button onClick={() => rotate(false)}>
                <i class="fa-solid fa-rotate-left"></i>
              </Button>
              <Button onClick={() => rotate(true)}>
                <i class="fa-solid fa-rotate-right"></i>
              </Button>
            </div>

            <div class={controlColumn}>
              <input
                type="range"
                min="0"
                max="65025"
                value={store?.brightness()}
                onInput={(e) => {
                  //brightness by square root 65025; min is 0 and max is 255
                  const brightness = Math.sqrt(parseInt(e.currentTarget.value));
                  store?.setBrightness(brightness);
                  sendBrightness(brightness);
                }}
              />
            </div>

            <div class={controlColumn}>
              <Show when={store?.plugin() === 1}>
                <Button onClick={() => loadImage()}>
                  <i class="fa-solid fa-file-import"></i>
                </Button>
                <Button onClick={clear}>
                  <i class="fa-solid fa-trash"></i>
                </Button>
                <Button
                  onClick={() => {
                    store?.toast(`Saved current state`, 1500);
                    wsMessage('persist');
                  }}
                >
                  <i class="fa-solid fa-floppy-disk"></i>
                </Button>
                <Button
                  onClick={() => {
                    store?.toast(`Saved state loaded`, 1500);
                    wsMessage('load');
                  }}
                >
                  <i class="fa-solid fa-refresh"></i>
                </Button>
              </Show>

              <a href="#/creator">creator</a>
            </div>
          </>
        }
      />
    </Show>
  );
};
