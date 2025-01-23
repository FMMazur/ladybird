// META: global=window,worker,shadowrealm
// META: script=../resources/recording-streams.js
// META: script=../resources/test-utils.js
'use strict';

// Tests for the use of pipeTo with AbortSignal.
// There is some extra complexity to avoid timeouts in environments where abort is not implemented.

const error1 = new Error('error1');
error1.name = 'error1';
const error2 = new Error('error2');
error2.name = 'error2';

const errorOnPull = {
  pull(controller) {
    // This will cause the test to error if pipeTo abort is not implemented.
    controller.error('failed to abort');
  }
};

// To stop pull() being called immediately when the stream is created, we need to set highWaterMark to 0.
const hwm0 = { highWaterMark: 0 };

promise_test(t => {
  const rs = recordingReadableStream(errorOnPull, hwm0);
  const ws = new WritableStream();
  const abortController = new AbortController();
  const signal = abortController.signal;
  abortController.abort();
  return promise_rejects_dom(t, 'AbortError', rs.pipeTo(ws, { signal }), 'pipeTo should reject')
      .then(() => Promise.all([
        rs.getReader().closed,
        promise_rejects_dom(t, 'AbortError', ws.getWriter().closed, 'writer.closed should reject')
      ]))
      .then(() => {
        assert_equals(rs.events.length, 2, 'cancel should have been called');
        assert_equals(rs.events[0], 'cancel', 'first event should be cancel');
        assert_equals(rs.events[1].name, 'AbortError', 'the argument to cancel should be an AbortError');
        assert_equals(rs.events[1].constructor.name, 'DOMException',
                      'the argument to cancel should be a DOMException');
      });
}, 'an aborted signal should cause the writable stream to reject with an AbortError');
